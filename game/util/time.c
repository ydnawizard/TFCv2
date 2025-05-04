
void getCurrentTime(time_t currentTime)
{
	currentTime=time(0);
}

int getTimeDiffSeconds(time_t minuend,time_t subtrahend)
{
	time_t diff=difftime(minuend, subtrahend);
	struct tm* timeDiff;
	timeDiff=localtime(&diff);
	int timeDiffSeconds=timeDiff->tm_sec;
	return timeDiffSeconds;
}

int getTimeDiffMinutes(time_t minuend,time_t subtrahend)
{
	time_t diff=difftime(minuend, subtrahend);
	struct tm* timeDiff;
	timeDiff=localtime(&diff);
	int timeDiffMinutes=timeDiff->tm_min;
	return timeDiffMinutes;
}
