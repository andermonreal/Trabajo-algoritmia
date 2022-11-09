#ifndef INFO
#define INFO

typedef struct info {
	double minAge;
	double maxAge;
	double minDebt;
	double maxDebt;
	double minYearsEmployed;
	double maxYearsEmployed;
	double minCreditScore;
	double maxCreditScore;
	double minIncome;
	double maxIncome;
} info;

void inicializarInfo(struct info *);

#endif