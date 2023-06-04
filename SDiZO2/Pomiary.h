#pragma once
class Pomiary {
public:
	void StartCounter();
	double GetCounter();
	double PCFreq = 0.0;
	__int64 CounterStart = 0;
};