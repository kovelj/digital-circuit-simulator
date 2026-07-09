# Digital Circuit Simulator

### Time domain digital circuit simulation engine

A lightweight, efficient C++ digital circuit simulator designed to model logic gates and signal transitions
over time. This tool allows users to define circuits via text files and observe state changes
(logic level transitions) at specific probe locations.

### Features
Supported Components

- Logic Gates: AND, OR, NOT.

- Signal Sources:

  - Clock Generator: Generates a periodic signal automatically.
  - Manual Clock Generator: Allows for user-triggered or manual signal pulsing.

- Monitoring:
  - Probe: Used to monitor and log state transitions at any specific point in the circuit.

### Usage

#### 1. Input File Format (circuit.txt)
Define your circuit layout in a text file using the following structure:

- Line 1: Total simulation duration in [us].
- Line 2: Number of components.
- Subsequent <number_of_components> Lines: Component definitions.
- Subsequence Lines: Connection mapping.

Example:
```log
10        # Simulation duration
2         # Number of components
1 1 1     # Component 1 (Generator)
2 0       # Component 2 (Probe)
1 2 0     # Connection between Component 1 and 2
```

#### 2. Components format
The simulator uses integer IDs to define components in the input netlist.
Each component line follows the logic defined below:

Probes:

| Netlist ID          | Type ID | Component | Description |
|:--------------------|:--------| :--- | :--- |
| positive int | 0 | Probe | Monitors state transitions |

```log
[Netlist ID] [Type ID]
```

Example:
```log
...
2 0       # Component 2 (Probe)
3 0       # Component 3 (Probe)
...
```

Clocks:

| Netlist ID          | Type ID | Frequency                                        | Component       | Description               |
|:--------------------|:--------|:-------------------------------------------------|:----------------|:--------------------------|
| positive int | 1 | Frequency (MHz)                         | Clock Generator | Automatic periodic signal |
| positive int | 2 | Sequence of time intervals (us) | Manual Clock    | User-defined transitions  |

```
[Netlist ID] [Type ID] [Frequency]
[Netlist ID] [Type ID] [Frequency] [T1] [T2] [T3] [T4] [T5] [T6] ...
```

Example:
```log
...
1 1 1           # Component 1 (Clock Generator), frequency 1[MHz]
2 1 0.2         # Component 2 (Clock Generator), frequency 0.2[MHz]
3 2 1 3 1 1 6 4 # Component 3 (Manual Clock Generator), Sequence of time intervals (us)
...
```

* **Logic for Manual Clock Generator:** The signal toggles at $1\mu s$, $4\mu s$ ($1+3\mu s$), $5\mu s$ 
($4+1\mu s$), $6\mu s$ ($5+1\mu s$), $12\mu s$ ($6+6\mu s$), and $16\mu s$ ($12+4\mu s$).

Gates:

| Netlist ID          | Type ID | Number of input pins | Component | Description |
|:--------------------|:--------|:---------------------|:----------| :--- |
| positive int | 3 |                      | NOT Gate  | Inverts input |
| positive int | 4 | positive int         | OR Gate   | Logic OR operation  |
| positive int | 5 | positive int         | AND Gate  | Logic AND operation |

```
[Netlist ID] [Type ID]
[Netlist ID] [Type ID] [Number of inputs]
[Netlist ID] [Type ID] [Number of inputs]
```

Example:

```log
...
4 4 2   # Component 4 (OR Gate) with 2 input pins
5 5 3   # Component 5 (AND Gate) with 3 input pins
6 3     # Component 6 (NOT Gate)
...
```

#### 3. Connections format
After every component is defined, subsequent lines represent connections between circuit component.

| Netlist ID1 | Netlist ID2 | Pin number                    | Description                             |
|:------------|:------------|:------------------------------|:----------------------------------------|
| ID_OUT      | ID_IN       | pin number of ID_IN component | Connect output from ID1 to input of ID2 |

#### 4. Understanding the Output
The simulator generates a chronological log of signal transitions for all probes:

```log
0 -> 1: 0.5us
1 -> 0: 1us
0 -> 1: 1.5us
...
```
Each entry indicates the state change (0 to 1 or 1 to 0) and the exact timestamp at which the transition occurred.

Output file name:

```log
<input_file_name>_output_<probe_ID>.txt
```
