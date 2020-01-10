## Baseball Tester

### Usage

 - Clone the repo or download all files
 - Open `tester.py` and update the `BASEBALL_EXE` variable to your compiled baseball program
 - Run `python tester.py` (must be python>=3.6)

Alternate files can be tested without modifying `tester.py` by supplying your executable as an argument to tester.py (e.g. `python tester.py ./softball`).

When the tester detects an error, it will print a summary and ask if you want to continue or exit. Continuing is default, so just press ENTER instead of typing 'c' if it makes it easier.

### Implementation Notes

If you're too lazy to update Python to >=3.6, you can try to make this program backwards compatible yourself! The only offending line (I think) is where I open a subprocess and include the argument `encoding='utf8'`. If you can figure something else out then you don't need to update Python.

If you happen to still care about Data Structures in tri 2 of your senior year, and if you happen to make this program backwards compatible, please fork this and submit a PR so I can merge it back in. Thanks!

### Report Problems

Solutions were generated from my program, which might not be entirely accurate. If you're finding that your program keeps failing a certain test case and you're sure it's right, let me know and I'll update the solutions if I think your correction is right.
