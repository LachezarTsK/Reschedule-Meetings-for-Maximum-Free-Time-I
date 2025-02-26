
function maxFreeTime(totalEventTime: number, maxNumberOfMeetingsToReschedule: number, startTime: number[], endTime: number[]): number {
    this.PLACEHOLDER_VALUE_FOR_FREE_TIME_BEFORE_FIRST_MEETING = -1;
    this.eventTimeRange = [0, totalEventTime];
    this.totalNumberOfMeetings = startTime.length;

    let maxFreeTime = 0;
    let currentFreeTime = startTime[0];
    let numberOfFreeTimeIntervals = startTime[0] > this.eventTimeRange[0] ? 1 : 0;

    let frontIndex = 0;
    let backIndex = startTime[0] > this.eventTimeRange[0] ? this.PLACEHOLDER_VALUE_FOR_FREE_TIME_BEFORE_FIRST_MEETING : 0;

    while (frontIndex < this.totalNumberOfMeetings) {

        if (numberOfFreeTimeIntervals < maxNumberOfMeetingsToReschedule + 1) {
            currentFreeTime += getValueToExpandFreeTime(startTime, endTime, frontIndex);
            ++frontIndex;
            ++numberOfFreeTimeIntervals;
        }

        maxFreeTime = Math.max(maxFreeTime, currentFreeTime);

        if (numberOfFreeTimeIntervals === maxNumberOfMeetingsToReschedule + 1) {
            currentFreeTime -= getValueToShrinkFreeTime(startTime, endTime, backIndex);
            ++backIndex;
            --numberOfFreeTimeIntervals;
        }
    }
    return maxFreeTime;

};

function getValueToExpandFreeTime(startTime: number[], endTime: number[], frontIndex: number): number {
    if (frontIndex + 1 < this.totalNumberOfMeetings) {
        return startTime[frontIndex + 1] - endTime[frontIndex];
    }
    return this.eventTimeRange[1] - endTime[frontIndex];
}

function getValueToShrinkFreeTime(startTime: number[], endTime: number[], backIndex: number): number {
    if (backIndex === this.PLACEHOLDER_VALUE_FOR_FREE_TIME_BEFORE_FIRST_MEETING) {
        return startTime[0];
    }
    return startTime[backIndex + 1] - endTime[backIndex];
}
