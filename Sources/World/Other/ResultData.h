#pragma once

struct ResultData
{
	bool isSuccessed = false;

	int progressDistance = 0;

	int itemUseCount = 0;

	int playMinutes = 0;
	int playSeconds = 0;
	int playTenMilliSeconds = 0;

	int distanceScore = 0;
	int itemScore = 0;
	int timeScore = 0;

	int overallScore = 0;
};
