# Machine Temperature Monitoring and Overheat Alert System

Final mini-project for `CSE321 Embedded System Design`.

This project is an embedded temperature monitoring system built around the `LPC2148` microcontroller. It reads temperature data from an `LM35` sensor, shows the live reading on a `16x2 LCD`, and raises an alert when the temperature crosses a fixed safety threshold.

It started as my final course mini-project and has been cleaned up here as a more presentable embedded systems portfolio project.

## What It Does

- Continuously reads machine temperature using `LM35`
- Converts analog sensor output to digital temperature data
- Displays the live temperature on a `16x2 LCD`
- Triggers an overheat alert when temperature exceeds `45 C`

## Hardware Used

- `LPC2148` ARM7 microcontroller
- `LM35` temperature sensor
- `16x2 LCD`
- `LED` for overheat indication

## LPC2148 Version

In the original version:

- `LM35` is connected to `P0.28` as `AD0.1`
- LCD is connected through `P1.16 - P1.25`
- Alert output is connected to `P0.10`

Temperature is calculated as:

```text
Temperature = (ADC_Value * 3.3 * 100) / 1024
```

## 8051 Version

This repo also includes an `8051` adaptation of the same project idea for comparison. Since a basic `8051` does not have a built-in ADC like the `LPC2148`, that version assumes an external ADC-based setup.

## Repository Structure

```text
.
|-- code/
|   |-- lpc2148.c
|   `-- 8051.c
|-- docs/
|   `-- report.pdf
`-- README.md
```

## Files

- [`code/lpc2148.c`](code/lpc2148.c) contains the original LPC2148 implementation
- [`code/8051.c`](code/8051.c) contains the 8051 adaptation
- [`docs/report.pdf`](docs/report.pdf) contains the original mini-project report

## Development Context

- Written in Embedded C
- Intended for `Keil uVision`
- Simulated in `Proteus`

## Why This Project

This project focuses on a simple but practical embedded systems flow:

- sensor interfacing
- ADC-based data acquisition
- LCD interfacing
- threshold-based control logic
- basic real-time monitoring and alerting

It is a small project, but it demonstrates the full path from hardware input to decision logic to user-visible output.
