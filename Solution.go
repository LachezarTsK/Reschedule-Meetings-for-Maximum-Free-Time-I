
package main

const PLACEHOLDER_VALUE_FOR_FREE_TIME_BEFORE_FIRST_MEETING = -1

var eventTimeRange [2]int
var totalNumberOfMeetings int

func maxFreeTime(totalEventTime int, maxNumberOfMeetingsToReschedule int, startTime []int, endTime []int) int {
    eventTimeRange = [2]int{0, totalEventTime}
    totalNumberOfMeetings = len(startTime)

    var maxFreeTime = 0
    var currentFreeTime = startTime[0]
    var numberOfFreeTimeIntervals = 0
    if startTime[0] > eventTimeRange[0] {
        numberOfFreeTimeIntervals = 1
    }

    var frontIndex = 0
    var backIndex = 0
    if startTime[0] > eventTimeRange[0] {
        backIndex = PLACEHOLDER_VALUE_FOR_FREE_TIME_BEFORE_FIRST_MEETING
    }

    for frontIndex < totalNumberOfMeetings {

        if numberOfFreeTimeIntervals < maxNumberOfMeetingsToReschedule + 1 {
            currentFreeTime += getValueToExpandFreeTime(startTime, endTime, frontIndex)
            frontIndex++
            numberOfFreeTimeIntervals++
        }

        maxFreeTime = max(maxFreeTime, currentFreeTime)

        if numberOfFreeTimeIntervals == maxNumberOfMeetingsToReschedule + 1 {
            currentFreeTime -= getValueToShrinkFreeTime(startTime, endTime, backIndex)
            backIndex++
            numberOfFreeTimeIntervals--
        }
    }
    return maxFreeTime
}

func getValueToExpandFreeTime(startTime []int, endTime []int, frontIndex int) int {
    if frontIndex + 1 < totalNumberOfMeetings {
        return startTime[frontIndex + 1] - endTime[frontIndex]
    }
    return eventTimeRange[1] - endTime[frontIndex]
}

func getValueToShrinkFreeTime(startTime []int, endTime []int, backIndex int) int {
    if backIndex == PLACEHOLDER_VALUE_FOR_FREE_TIME_BEFORE_FIRST_MEETING {
        return startTime[0]
    }
    return startTime[backIndex + 1] - endTime[backIndex]
}
