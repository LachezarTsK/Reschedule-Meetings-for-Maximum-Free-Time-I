
#include <vector>
#include <algorithm>
using namespace std;


class Solution {

    static const int PLACEHOLDER_VALUE_FOR_FREE_TIME_BEFORE_FIRST_MEETING = -1;

    array<int, 2> eventTimeRange{};
    int totalNumberOfMeetings{};

public:
    int maxFreeTime(int totalEventTime, int maxNumberOfMeetingsToReschedule, vector<int>& startTime, vector<int>& endTime) {
        eventTimeRange[1] = totalEventTime;
        totalNumberOfMeetings = startTime.size();

        int maxFreeTime = 0;
        int currentFreeTime = startTime[0];
        int numberOfFreeTimeIntervals = startTime[0] > eventTimeRange[0] ? 1 : 0;

        int frontIndex = 0;
        int backIndex = startTime[0] > eventTimeRange[0] ? PLACEHOLDER_VALUE_FOR_FREE_TIME_BEFORE_FIRST_MEETING : 0;

        while (frontIndex < totalNumberOfMeetings) {

            if (numberOfFreeTimeIntervals < maxNumberOfMeetingsToReschedule + 1) {
                currentFreeTime += getValueToExpandFreeTime(startTime, endTime, frontIndex);
                ++frontIndex;
                ++numberOfFreeTimeIntervals;
            }

            maxFreeTime = max(maxFreeTime, currentFreeTime);

            if (numberOfFreeTimeIntervals == maxNumberOfMeetingsToReschedule + 1) {
                currentFreeTime -= getValueToShrinkFreeTime(startTime, endTime, backIndex);
                ++backIndex;
                --numberOfFreeTimeIntervals;
            }
        }
        return maxFreeTime;
    }

private:
    int getValueToExpandFreeTime(span<const int> startTime, span<const int> endTime, int frontIndex) const {
        if (frontIndex + 1 < totalNumberOfMeetings) {
            return startTime[frontIndex + 1] - endTime[frontIndex];
        }
        return eventTimeRange[1] - endTime[frontIndex];
    }

    int getValueToShrinkFreeTime(span<const int> startTime, span<const int> endTime, int backIndex) const {
        if (backIndex == PLACEHOLDER_VALUE_FOR_FREE_TIME_BEFORE_FIRST_MEETING) {
            return startTime[0];
        }
        return startTime[backIndex + 1] - endTime[backIndex];
    }
};
