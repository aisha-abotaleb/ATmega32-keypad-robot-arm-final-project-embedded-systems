# Robotic Arm Control using AVR and 4x4 Keypad
![Simulation on proteus](./Robotic_arm_using_KPD/simulation_on_proteus.png)



This project controls a **robotic arm** equipped with 4 servo motors using a single AVR microcontroller and a 4x4 matrix keypad.

- **Servo 1 (Base)**: Left/Right rotation.
- **Servo 2 & 3 (Arm)**: Move together to drive the arm forward and backward.
- **Servo 4 (Gripper)**: Open and close the gripper.

---

## Key Mapping

Based on the 4x4 keypad layout used:

| Key | Action |
|-----|--------|
| `8` | Move arm **Forward** |
| `2` | Move arm **Backward** |
| `4` | Rotate base **Left** |
| `6` | Rotate base **Right** |
| `5` | Toggle gripper (**Catch / Release**) |

---

## 🛠️ Components Used

- AVR microcontroller (ATMega32 or equivalent)
- 4 Servo motors
- 4x4 Matrix Keypad
- (Optional) 16x2 LCD for status display

---

## 📂 Project Structure

```
├── main.c          # Main control logic
├── LIB/
│   ├── STD_TYPES.h
│   └── BIT_MATH.h
├── MCAL/
│   ├── DIO.h / DIO.c
│   ├── GI.h / GI.c
│   └── Timers.h / Timers.c
└── HAL/
    ├── KPD.h / KPD.c      # Keypad driver
    └── LCD.h / LCD.c      # LCD driver
```

---


## Important Notes for Practical Implementation

### 1. Power Supply (The #1 Reason Hardware Fails)

You will likely notice that **your code runs flawlessly in simulation** (e.g., Proteus, AVR Simulator). The keypad responds, the logic executes, and everything 
