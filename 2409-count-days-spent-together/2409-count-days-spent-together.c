
int countDaysTogether(char* arriveAlice, char* leaveAlice,
                      char* arriveBob, char* leaveBob) {
    int days[] = {31, 28, 31, 30, 31, 30,
                  31, 31, 30, 31, 30, 31};

    int a1 = (arriveAlice[0] - '0') * 10 + arriveAlice[1] - '0';
    int a2 = (arriveAlice[3] - '0') * 10 + arriveAlice[4] - '0';
    int l1 = (leaveAlice[0] - '0') * 10 + leaveAlice[1] - '0';
    int l2 = (leaveAlice[3] - '0') * 10 + leaveAlice[4] - '0';

    int b1 = (arriveBob[0] - '0') * 10 + arriveBob[1] - '0';
    int b2 = (arriveBob[3] - '0') * 10 + arriveBob[4] - '0';
    int r1 = (leaveBob[0] - '0') * 10 + leaveBob[1] - '0';
    int r2 = (leaveBob[3] - '0') * 10 + leaveBob[4] - '0';

    int startA = a2, endA = l2;
    int startB = b2, endB = r2;

    for (int i = 0; i < a1 - 1; i++) startA += days[i];
    for (int i = 0; i < l1 - 1; i++) endA += days[i];
    for (int i = 0; i < b1 - 1; i++) startB += days[i];
    for (int i = 0; i < r1 - 1; i++) endB += days[i];

    int start = startA > startB ? startA : startB;
    int end = endA < endB ? endA : endB;

    return end >= start ? end - start + 1 : 0;
}
