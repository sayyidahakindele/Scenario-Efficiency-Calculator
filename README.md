# Scenario Efficiency Calculator

AUTHOR 
------
Doyinsola Sayyidah Akindele


PURPOSE
-------
Simulates a fight between two heroes, Tortoise and Hare, against a crew of ten pirates. Each scenario gives an advantage to a particular hero by giving them a magic sword.
- Scenario 1: Tortoise gets the magic sword
- Scenario 2: Hare gets the magic sword
- Scenario 3: No one gets the sword.

Statistics for each run are accumulated and printed at the end.

From the statistics we can deduce which scenario is most efficient

TECHNICAL SKILLS
----------------
This program utilizes multi-threading to multiple scenarios simultaneously, employing semaphores and mutexes for data sharing.

COMPILING AND LAUNCHING
------------------------
1. make
2. ./fp n, where n is the number of runs
   - default is 100; ./fp


FILES
-------------------------------
- defs.h
- main.c
- deque.c
- fighter.c
- stats.c
- fight.c
- MAKEFILE
