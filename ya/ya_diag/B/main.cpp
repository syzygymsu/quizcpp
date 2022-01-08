#include <iostream>
#include <string>
#include <vector>
#include <ctime>
// #include <locale>
#include <iomanip>

namespace {

    static const char* format = "%Y-%m-%d";

    struct Period
    {
        std::tm startDate = {0};
        std::tm endDate = {0};
    };

    typedef std::vector<Period> vecPeriods;

    bool StartDateLessThanEnd(std::tm startDate, std::tm endDate)
    {
        std::time_t start = std::mktime(&startDate);
        std::time_t end = std::mktime(&endDate);
        double aux = std::difftime(end, start);
        if (aux > 0)
        {
            return true;
        }
        return false;
    }

    void print(const Period& period) {
        std::cout << std::put_time(&period.startDate, format);
        std::cout << ' ';
        std::cout << std::put_time(&period.endDate, format);
        std::cout << '\n';
    }

    void CheckIfEndOfPeriodCorrect(Period& temp_pair, std::tm endDate)
    {
        std::time_t start = std::mktime(&temp_pair.endDate);
        std::time_t end = std::mktime(&endDate);
        double aux = std::difftime(start, end);
        if (aux >= 0)
        {
            temp_pair.endDate = endDate;
        }
    }

    void Normalize(std::tm& curDate)
    {
        time_t next = mktime(&curDate);
    }

    std::tm AddDays(std::tm curDate, int days)
    {
        curDate.tm_mday += days;
        time_t next = mktime(&curDate);
        return curDate;
    }

    int GetDaysInMonth(const std::tm& curDate)
    {
        std::tm date = curDate;
        int i = 0;
        for (i = 29; i <= 31; i++)
        {
            date.tm_mday = i;
            mktime(&date);
            if (date.tm_mon != curDate.tm_mon)
            {
                break;
            }
        }
        return i - 1;
    }

    std::tm MONTHEndDate(std::tm curDate)
    {
        curDate.tm_mday = GetDaysInMonth(curDate);
        return curDate;
    }

    std::tm WEEKEndDate(std::tm curDate)
    {
        int DaysTillSunday = 7 - (int)curDate.tm_wday;
        if (DaysTillSunday == 7)
        {
            DaysTillSunday = 0;
        }

        std::tm date = AddDays(curDate, DaysTillSunday);
        return date;
    }

    std::tm REVIEWEndDate(std::tm curDate)
    {
        std::tm date2 = curDate;
        if (curDate.tm_mon >= 3 && curDate.tm_mon <= 8)
        {//summer time
            date2.tm_mon = 8;//September
            date2.tm_mday = 30;
        }
        else
        { //Winter time
            date2.tm_year = curDate.tm_mon <= 11 ? curDate.tm_year + 1 : curDate.tm_year;
            date2.tm_mon = 2;//March
            date2.tm_mday = 31;
        }
        Normalize(date2);
        return date2;
    }

    std::tm YEAREndDate(std::tm curDate)
    {
        //YEAR — год c 1 января по 31 декабря.
        std::tm date = curDate;
        date.tm_mon = 11;//Dec
        date.tm_mday = 31;
        return date;
    }

    std::tm QUARTEREndDate(std::tm curDate)
    {
        //интервалы в три месяца: январь — март, апрель — июнь, июль — сентябрь, октябрь — декабрь.
        //Спионерил в интернете
        int quarterNumber = (curDate.tm_mon) / 3 + 1;
        std::tm firstDayOfQuarter = curDate;
        firstDayOfQuarter.tm_mon = (quarterNumber - 1) * 3;
        firstDayOfQuarter.tm_mday = 1;
        Normalize(firstDayOfQuarter);

        auto lastDayOfQuarter = firstDayOfQuarter;
        lastDayOfQuarter.tm_mon += 3;
        Normalize(lastDayOfQuarter);
        lastDayOfQuarter.tm_mday -= 1;
        Normalize(lastDayOfQuarter);

        return lastDayOfQuarter;
    }

    typedef std::tm(*PeriodProcessingDelegate)(std::tm curDate);

    vecPeriods ProcessPeriod(const Period& p, PeriodProcessingDelegate func)
    {
        vecPeriods listOfPeriods;

        std::tm curDate = p.startDate;

        Period temp_pair;
        temp_pair.startDate = curDate;
        temp_pair.endDate = func(curDate);

        CheckIfEndOfPeriodCorrect(temp_pair, p.endDate);

        listOfPeriods.push_back(temp_pair);
        curDate = temp_pair.endDate;

        while (StartDateLessThanEnd(curDate, p.endDate))
        {
            Period temp_pair;
            temp_pair.startDate = AddDays(curDate, 1);
            temp_pair.endDate = func(temp_pair.startDate);
            listOfPeriods.push_back(temp_pair);
            curDate = temp_pair.endDate;
        }
        if (listOfPeriods.size() > 1)
        {
            //trim last period
            CheckIfEndOfPeriodCorrect(listOfPeriods.back(), p.endDate);
        }
        return listOfPeriods;
    }
}

int main()
{
    vecPeriods listOfPeriods;
    std::string sPeriodType;
    std::cin >> sPeriodType;

    Period p;
    std::cin >> std::get_time(&p.startDate, format);
    std::cin >> std::get_time(&p.endDate, format);
    Normalize(p.startDate);
    Normalize(p.endDate);

    if (sPeriodType == "WEEK") {
        listOfPeriods = ProcessPeriod(p, WEEKEndDate);
    } else if (sPeriodType == "MONTH") {
        listOfPeriods = ProcessPeriod(p, MONTHEndDate);
    } else if (sPeriodType == "REVIEW") {
        listOfPeriods = ProcessPeriod(p, REVIEWEndDate);
    } else if (sPeriodType == "YEAR") {
        listOfPeriods = ProcessPeriod(p, YEAREndDate);
    } else if (sPeriodType == "QUARTER") {
        listOfPeriods = ProcessPeriod(p, QUARTEREndDate);
    }

    std::cout << listOfPeriods.size() << '\n';
    for (const Period& p : listOfPeriods) {
        print(p);
    }
    std::cout << std::flush;

}
