#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class webpage {
private:
    string link;
    vector<string> keywords;
    double numofimpressions;
    double numberofclicks;
    double ClickThroughRate;
    int pageNumber;
    double pageRank;
    double pageScore;
    vector<int> ponitedto;
    vector<int> pointedAtBy;


public:

    webpage()
    {
        ponitedto.resize(0);
        link = " ";
        numberofclicks = 0;
        numofimpressions = 1;
        ClickThroughRate = (numberofclicks / numofimpressions) * 100;
        keywords.resize(10);
        pageScore = 0;
        pageRank = 0;
        pointedAtBy.resize(0);
    }
    void addPage(int x)
    {
        ponitedto.push_back(x);
    }
    vector<int> getlinkedpages()
    {
        return ponitedto;
    }
    void addpointedatpage(int x)
    {
        pointedAtBy.push_back(x);
    }
    vector<int> getpointedatpages()
    {
        return pointedAtBy;
    }

    webpage(string LINK, vector<string> KEYWORDS, int IMPRESSIONNUM, int PAGENUMBER, int clicknum)
    {
        link = LINK;
        numberofclicks = clicknum;
        numofimpressions = IMPRESSIONNUM;
        ClickThroughRate = (numberofclicks / numofimpressions) * 100;
        keywords = KEYWORDS;
        pageScore = 0;
        pageNumber = PAGENUMBER;
    }
    //SETTERS
    void setPageNumber(int x)
    {
        pageNumber = x;
    }
    void setLink(string LINK)
    {
        link = LINK;
    }
    void setkeywords(vector<string> KEYWORDS)
    {
        keywords = KEYWORDS;
    }
    void setNumofImpressions(int x)
    {
        numofimpressions = x;
        if (x != 0)
        {
            ClickThroughRate = (numberofclicks / numofimpressions) * 100;
            setscore();
        }
    }
    void setNumberOfClicks(int x)
    {
        numberofclicks = x;
        ClickThroughRate = (numberofclicks / numofimpressions) * 100;
        setscore();
    }
    void setCRT(double x)
    {
        ClickThroughRate = x;
    }
    void setscore()
    {
        pageScore = 0.4 * pageRank + ((1 - (0.1 * numofimpressions) / (1 + 0.1 * numofimpressions)) * pageRank + ((0.1 * numofimpressions) / (1 + 0.1 * numofimpressions)) * ClickThroughRate) * 0.6;
    }
    void setPageRank(double x)
    {
        pageRank = x;
        setscore();
    }
    //GETTERS
    double getPagescore()
    {
        setscore();
        return pageScore;
    }
    int getPageNum()
    {
        return pageNumber;
    }
    double GetPageRank()
    {
        return pageRank;
    }
    string getlink()
    {
        return link;
    }
    vector<string> getkeywords()
    {
        return keywords;
    }
    double getimpressions()
    {
        return numofimpressions;
    }
    double getclickNum()
    {
        return numberofclicks;
    }
    double getCRT()
    {
        return ClickThroughRate;
    }
    //CHANGING FUNCTIONS
    //IF PAGE APPEARED IN SREARCH, IMPRESSIONS AND CLICKS CHANGE, PAGE SCORE GHANGES
    void changeImp()
    {
        numofimpressions++;
        ClickThroughRate = (numberofclicks / numofimpressions) * 100;
        setscore();
    }
    void changeClickNum()
    {
        // adjuscting score and click through rate everytime a webpage is clicked
        numberofclicks++;
        ClickThroughRate = (numberofclicks / numofimpressions) * 100;
        setscore();
    }
    void printWebpage()
    {
        cout << link << endl;
        cout << "keywords" << endl;
        for (int i = 0; i < keywords.size(); i++)
            cout << keywords[i] << endl;
        cout << "Impressions: " << numofimpressions << endl;
        cout << "clicks: " << numberofclicks << endl;
        cout << "CTR " << ClickThroughRate << endl;
        cout << "pagescore " << pageScore << endl;
    }


};



