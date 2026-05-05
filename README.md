# manage_csv_cs32

A terminal-based CSV record management tool written in C. It manages two linked CSV files — **old data** (`p_data.csv`) and **young data** (`n_data.csv`) — with an interactive arrow-key menu interface.

---

## Requirements

- GCC (or any C compiler)
- GNU Make
- A POSIX-compatible terminal (Linux / WSL)

---

## Build

```bash
git clone https://github.com/Loveberland/manage_csv_cs32.git
cd manage_csv_cs32
make
```

This compiles all source files and produces the `manage_csv_cs32` executable.

---

## Run

```bash
./manage_csv_cs32
# or simply
make run
```

---

## Navigation

All menus use the **arrow keys** to move the highlight and **Enter** to confirm.

```
 -> input        ← currently selected (green highlight)
    edit
    delete
    display
    exit
```

---

## Main Menu Options

### `input` — Add a new record

After selecting `input`, choose which CSV file to write to:

| Option | File        | Fields recorded |
|--------|-------------|-----------------|
| `old`  | `p_data.csv` | ID, First name, Last name, Nick name, Role, Disease, Drug allergy, Food, Other |
| `young`| `n_data.csv` | ID, First name, Last name, Nick name, Disease, Drug allergy, Food, Other, **Linked ID** |

Select `back` to return to the main menu without saving.

---

### `delete` — Remove a record by ID

After selecting `delete`, choose which file to target (`old` / `young`), then type the ID to delete.

```
ID: P8001
```

- If the ID is found, the matching row is removed from the file and the action is logged to `logs.txt`.
- If the ID is not found, the file is left unchanged and a note is written to the log.

---

### `display` — View records

Choose a display mode:

| Option | Description |
|--------|-------------|
| `all`  | Prints every record in `p_data.csv`, with any linked records from `n_data.csv` shown indented below each person |
| `one`  | Prompts for an ID and prints only that record (plus linked entries if applicable) |

Example output for `display → one`:

```
ID,  First name,  Last name,  Nick name,  Role,  Disease,  Drug allergy,  Food,  Other
P8001,  John,  Doe,  Johnny,  Patient,  None,  Penicillin,  Vegan,  -
    ID,  First name,  Last name,  Nick name,  Disease,  Drug allergy,  Food,  Other,  Linked ID
    N9001,  Jane,  Doe,  Janie,  None,  None,  None,  -,  P8001
```

---

### `exit` — Quit the program

Closes `logs.txt` cleanly and exits.

---

## CSV File Structure

Both CSV files contain a **header row** as their first line.

**`p_data.csv`**
```
ID, First name, Last name, Nick name, Role, Disease, Durk allergy, Food, Other
```

**`n_data.csv`**
```
ID, First name, Last name, Nick name, Disease, Durk allergy, Food, Other, Linked ID
```

> Do not remove the header row — the display logic reads it to print column labels.

---

## Logging

All `input` and `delete` operations are appended to `logs.txt` with a timestamp:

```
[2025-05-01 14:32:10]: put P8001, John, Doe, Johnny, Patient, None, Penicillin, Vegan, - to p_data.csv
[2025-05-01 14:35:22]: delete data id[P8001]
```

---

## Running Tests

```bash
make test_choice    # Tests the interactive menu (choice module)
make test_time      # Tests the timestamp formatter (time_manager module)
```

---

## Clean Build Artifacts

```bash
make clean
```

Removes the `out/` directory, compiled binaries, and test executables.

---

## Project Structure

```
manage_csv_cs32/
├── main.c              # Entry point, main loop
├── choice.c / .h       # Arrow-key menu handlers
├── input.c / .h        # Record input logic
├── display.c / .h      # Record display logic
├── delete.c / .h       # Record deletion logic
├── time_manager.c / .h # Timestamp utility
├── p_data.csv          # Patient records (with header row)
├── n_data.csv          # Linked records (with header row)
├── logs.txt            # Operation log (auto-created/appended)
└── makefile
```
