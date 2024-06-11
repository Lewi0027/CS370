This is HW2.

checker.c:
    int main()
        checks if value1 is divisble by value2, returns 0 or 1 and has printf() statements.

coordinator.c:
    int main()
        passes five arguments to coordinator
    void coordinator()
        creates four forks and ensures parent waits for child to finish before proceeding.
        each fork calls checker