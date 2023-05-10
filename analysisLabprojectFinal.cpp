// analysisLabProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<sstream>
#include <stdlib.h >
#include "webpageClass.cpp"
using namespace std;
vector<string> readFile(string filename)
{
    // returns a vector of strings containing the input of the file
    vector<string> data;
    data.resize(0);
    ifstream file;
    file.open(filename);

    string input;
    int i = 0;
    while (!file.eof())
    {
        file >> input;
        data.push_back(input);
        i++;
    }
    return data;

}
int InitializeWebpages(vector<webpage>& webpages)
{

    vector<string> contentImpressions = readFile("impressions2.csv");
    vector<string> contentClicks = readFile("clicks2.csv");
    int numofWebapges = contentImpressions.size();
    vector<string> Keywords = readFile("keywords.csv");
    /*for (int i = 0; i < Keywords.size(); i++)
        cout << Keywords[i] << endl;*/
    webpages.resize(numofWebapges);
    for (int i = 0; i < numofWebapges; i++)
    {
        //initialize links
        string tempstring;
        int counter1 = 0;
        while (contentImpressions[i][counter1] != ',')
        {
            counter1++;
        }

        for (int j = 0; j < counter1; j++)
        {

            tempstring.push_back(contentImpressions[i][j]);
        }
        webpages[i].setLink(tempstring);
        /*cout << webpages[i].getlink() << endl;*/
        //initialize page index
        webpages[i].setPageNumber(i + 1);
        /*cout << webpages[i].getPageNum() << endl;*/

        tempstring = "";
        //initialize number of impressions

        for (int j = 0; j < contentImpressions[i].size() - 1; j++)
        {

            counter1++;
            if (counter1 > contentImpressions[i].size() - 1)
                break;
            tempstring.push_back(contentImpressions[i][counter1]);
        }
        webpages[i].setNumofImpressions(stoi(tempstring));
        /* cout << webpages[i].getimpressions() << endl;*/
    }
    // initializing keywords
    for (int i = 0; i < numofWebapges; i++)
    {
        vector<string>tempKeywords;
        tempKeywords.resize(0);
        string tempstring;
        int counter1 = 0;
        int counter2 = 0;
        while (counter1 != Keywords[i].size())
        {
            //while line did not end
            //first semi colon will be link so disregarded
            while (Keywords[i][counter1] != ',')
            {
                counter1++;
            }
            counter1++;
            counter2 = counter1;
            while (Keywords[i][counter2] != ',' && counter2 != Keywords[i].size())
            {
                counter2++;
            }

            for (int j = counter1++; j < counter2; j++)
            {
                if (Keywords[i][j] == '.')
                    tempstring.push_back(' ');
                else
                {
                    tempstring.push_back(Keywords[i][j]);
                }
            }
            tempKeywords.push_back(tempstring);
            counter1 = counter2;
            counter2 = 0;
            tempstring.clear();
        }
        webpages[i].setkeywords(tempKeywords);
        tempKeywords.clear();
        /* tempKeywords = webpages[i].getkeywords();
         for (int i = 0; i < tempKeywords.size(); i++)
         {
             cout << tempKeywords[i]<<endl;
         }*/

    }
    //for (int i = 0; i < numofWebapges; i++)
    //{
    //    string tempstring;
    //    int counter1 = 0;
    //    while (contentClicks[i][counter1] != ',')
    //    {
    //        counter1++;
    //    }

    //    tempstring = "";
    //    //initialize number of clicks

    //    for (int j = 0; j < contentClicks[i].size() - 1; j++)
    //    {

    //        counter1++;
    //        if (counter1 > contentClicks[i].size() - 1)
    //            break;
    //        tempstring.push_back(contentClicks[i][counter1]);
    //    }
    //    webpages[i].setNumberOfClicks(stoi(tempstring));
    //    /* cout << webpages[i].getimpressions() << endl;*/
    //}


    return numofWebapges;

}
int findWebpageNumber(string x, vector<webpage>& pages, int numberOfwebpages)
{

    for (int i = 0; i < numberOfwebpages; i++)
    {

        if (x == pages[i].getlink())
        {
            return (i);
        }

    }


}
void linkPages(vector<webpage>& pages, int numberofwebpages)
{
    vector<string> file = readFile("webgraph.csv");
    int size = file.size();
    string link1 = "";
    string link2 = "";

    for (int i = 0; i < size; i++)
    {
        int counter1 = 0;
        while (file[i][counter1] != ',')
        {
            counter1++;
        }

        for (int j = 0; j < counter1; j++)
        {
            link1.push_back(file[i][j]);
        }
        counter1++;
        int webpage1 = findWebpageNumber(link1, pages, numberofwebpages);
        link1.clear();
        int counter2 = file[i].size();
        for (int j = counter1; j < counter2; j++)
        {
            link2.push_back(file[i][j]);
        }
        int webpage2 = findWebpageNumber(link2, pages, numberofwebpages);
        link2.clear();
        // add index of linkef page
        pages[webpage1].addPage(webpage2 + 1);
        pages[webpage2].addpointedatpage(webpage1 + 1);
    }

    //testing
    /*for (int i = 0; i < numberofwebpages; i++)
    {
        vector<int> page= pages[i].getlinkedpages();
        cout << i+1 << "---> ";
        for (int j = 0; j < page.size(); j++)
            cout << page[j] <<" ";
        cout<< endl;
    }*/

}
double calculateMeanPagerank(vector<webpage>& pages, int numberOfWebpages)
{
    double mean = 0;

    for (int i = 0; i < numberOfWebpages; i++)
    {
        mean = mean + pages[i].GetPageRank();
    }
    mean = mean / numberOfWebpages;
    return mean;

}
void calculatePageRank(vector<webpage>& pages, int numberOFwebpages)
{

    double initialValue = 1.0 / numberOFwebpages;
    vector<double> previousPageRanks(numberOFwebpages, 0);
    //cout << "initial pageranks" << endl;
    for (int i = 0; i < numberOFwebpages; i++)
    {
        pages[i].setPageRank(initialValue);
        // cout << pages[i].GetPageRank()<< endl;
    }

    /*for (int i = 0; i < 2; i++)
    {*/

    int i = 0;
    while (previousPageRanks[0] - pages[0].GetPageRank() > 0.001 || i < 100)
    {


        for (int i = 0; i < numberOFwebpages; i++)
        {
            previousPageRanks[i] = pages[i].GetPageRank();
            // cout << previousPageRanks[i] << endl;
        }

        //cout << "iteration " << i << endl;
        for (int j = 0; j < numberOFwebpages; j++)
        {
            vector<int>pintedatBy = pages[j].getpointedatpages();

            double sum = 0;
            for (int z = 0; z < pintedatBy.size(); z++)
            {
                int w = pintedatBy[z] - 1;
                double x = previousPageRanks[w];
                double y = pages[w].getlinkedpages().size();
                double k = (x / y);
                sum = sum + k;
            }
            sum = 0.15 + 0.85 * (sum);// this includes damping factor
            double mean = calculateMeanPagerank(pages, numberOFwebpages);
            pages[j].setPageRank(sum / mean);
            //cout << pages[j].GetPageRank()<< endl;

        }
        i++;
    }

    //}

}
void merge(vector<double> array, int const left, int const mid, int const right)
{
    auto const tempArray1 = mid - left + 1;
    auto const tempArray2 = right - mid;

    auto* l = new double[tempArray1],
        * r = new double[tempArray2];

    for (auto i = 0; i < tempArray1; i++)
        l[i] = array[left + i];
    for (auto j = 0; j < tempArray2; j++)
        r[j] = array[mid + 1 + j];

    auto index1 = 0,
        index2 = 0;
    int mergedindex = left;
    while (index1 < tempArray1 && index2 < tempArray2) {
        if (l[index1] >= r[index2]) {
            array[mergedindex] = l[index1];
            index1++;
        }
        else {
            array[mergedindex] = r[index2];
            index2++;
        }
        mergedindex++;
    }
    while (index1 < tempArray1) {
        array[mergedindex] = l[index1];
        index1++;
        mergedindex++;
    }
    while (index2 < tempArray2) {
        array[mergedindex] = r[index2];
        index2++;
        mergedindex++;
    }
}
void mergeSort(vector<double> v, int const begin, int const end)
{
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(v, begin, mid);
    mergeSort(v, mid + 1, end);
    merge(v, begin, mid, end);
}
void removeDuplicates(vector<double>& v, int size)
{

    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] == v[i - 1])
        {
            v.erase(v.begin() + i, v.begin() + i + 1);
        }
    }

}
void printData(vector<webpage>& pages, int numberOFwebpages)
{
    /*for(int i=0; i<numberOFwebpages; i++)
    {
        cout<<pages[i].getlink()<<endl;
    }*/
    //to update files
    ofstream outputfile;
    outputfile.open("impressions2.csv");
    for (int i = 0; i < numberOFwebpages; i++)
    {
        if (i + 1 == numberOFwebpages)
        {
            outputfile << pages[i].getlink() << "," << pages[i].getimpressions();
        }
        else
        {
            outputfile << pages[i].getlink() << "," << pages[i].getimpressions() << endl;
        }
    }
    outputfile.close();
    ofstream outputfile2;
    outputfile2.open("clicks2.csv");
    for (int i = 0; i < numberOFwebpages; i++)
    {
        if (i + 1 == numberOFwebpages)
        {
            outputfile2 << pages[i].getlink() << "," << pages[i].getclickNum();
        }
        else
        {
            outputfile2 << pages[i].getlink() << "," << pages[i].getclickNum() << endl;
        }
    }
    outputfile2.close();
}
void ProcessSearcch(vector<webpage>& pages, int numberOFwebpages);
void display2(vector<webpage> relevantPages, vector<webpage> pages, int numberOFwebpages);
void display3(vector<webpage> relevantPages, vector<webpage> pages, int numberOFwebpages)
{
    system("CLS");
    cout << "Here are the results for your search : " << endl;
    cout << "-------------------" << endl;
    for (int i = 0; i < relevantPages.size(); i++)
    {
        cout << i + 1 << "- " << relevantPages[i].getlink() << endl;

    }
    for (int i = 0; i < relevantPages.size(); i++)
    {
        for (int j = 0; j < numberOFwebpages; j++)
        {
            if (relevantPages[i].getPageNum() == pages[j].getPageNum())
            {
                pages[j].changeImp();
                // it will be displayed--> we need to change the number of impressions
                //updating files
                printData(pages, numberOFwebpages);
            }

        }
    }
    int choice;
    if (relevantPages.size() == 0)
    {
        cout << "No relevant Webpages!" << endl;
        cout << "Would you like to" << endl;
        cout << "2- New search" << endl;
        cout << "3- Exit" << endl;
    }
    else {

        cout << "Would you like to" << endl;
        cout << "1- Choose a webpage to open" << endl;
        cout << "2- New search" << endl;
        cout << "3- Exit" << endl;
        cout << "Type in your choice:(please type 1,2 or 3) ";
    }

    cin >> choice;
    if (choice == 1)
    {
        int WebsiteChoice;
        cout << "Choose a website! \n";
        cin >> WebsiteChoice;
        if (WebsiteChoice <= 0 || WebsiteChoice > relevantPages.size())
            cout << "wrong entry!" << endl;
        else {
            cout << "\n You're now viewing " << relevantPages[WebsiteChoice - 1].getlink() << endl;
            for (int i = 0; i < numberOFwebpages; i++)
            {
                if (relevantPages[WebsiteChoice - 1].getPageNum() == pages[i].getPageNum())
                {
                    pages[i].changeClickNum();
                    //updating files
                    printData(pages, numberOFwebpages);
                }
            }
        }
        display2(relevantPages, pages, numberOFwebpages);
    }
    else if (choice == 2)
    {
        ProcessSearcch(pages, numberOFwebpages);
    }
    else if (choice == 3)
    {

        exit(0);
    }

}
void display2(vector<webpage> relevantPages, vector<webpage> pages, int numberOFwebpages)
{

    int choice;
    cout << "What would you like to do?" << endl;
    cout << "1- Back to search results" << endl;
    cout << "2- New search" << endl;
    cout << "3- Exit" << endl;
    cout << "Your choice: ";
    cin >> choice;
    system("CLS");
    if (choice == 1)
    {

        display3(relevantPages, pages, numberOFwebpages);
    }
    else if (choice == 2)
    {
        ProcessSearcch(pages, numberOFwebpages);
    }
    else if (choice == 3)
    {

        exit(0);
    }
}
void ProcessSearcch(vector<webpage>& pages, int numberOFwebpages)
{
    string searchEntry;
    string temp;
    bool AND = 0;
    bool OR = 0;
    bool quote = 0;

    cout << "what do you want to search for?" << endl;
    cin.ignore();
    getline(cin, searchEntry);
    stringstream split(searchEntry);


    if (searchEntry[0] == '"')
    {
        quote = true;
    }
    while (split.good())
    {
        string s;
        getline(split, s, ' ');
        if (s == "AND" || s == "and")
        {
            AND = true;
        }
        else if (s == "OR" || s == "or")
        {
            OR = true;
        }

    }
    if (AND == false && OR == false && quote == false)
    {
        // case of 1 keyword--> no splitting
        stringstream split(searchEntry);
        vector<string> keyWords;
        vector<string> searchkeyWords;
        keyWords.resize(0);
        vector<webpage> relevantPages;
        relevantPages.resize(0);;
        vector<double> scores;
        while (split.good())
        {
            string temp;
            getline(split, temp, ' ');
            searchkeyWords.push_back(temp);

        }


        for (int i = 0; i < numberOFwebpages; i++)
        {
            keyWords = pages[i].getkeywords();
            for (int j = 0; j < searchkeyWords.size(); j++)
            {
                for (int k = 0; k < keyWords.size(); k++)
                {
                    if (keyWords[k] == searchkeyWords[j])
                    {
                        double x = pages[i].getPagescore();
                        scores.push_back(x);
                    }
                }

            }

        }
        mergeSort(scores, 0, scores.size() - 1); // we sort scores to be able to remove dupilicates
        removeDuplicates(scores, scores.size()); //now we have all the relevant webages to the search query, we need to sort page scores 
        for (int i = 0; i < scores.size(); i++)
        {
            for (int j = 0; j < numberOFwebpages; j++)
            {
                if (scores[i] == pages[j].getPagescore())
                {
                    relevantPages.push_back(pages[j]);
                    pages[j].changeImp();
                    // it will be displayed--> we need to change the number of impressions
                    //updating files
                    printData(pages, numberOFwebpages);
                }

            }
        }

        cout << "Here are the results for your search : " << endl;
        cout << "-------------------" << endl;
        for (int i = 0; i < relevantPages.size(); i++)
        {
            cout << i + 1 << "- " << relevantPages[i].getlink() << endl;

        }
        int choice;
        if (relevantPages.size() == 0)
        {
            cout << "No relevant Webpages!" << endl;
            cout << "Would you like to" << endl;
            cout << "2- New search" << endl;
            cout << "3- Exit" << endl;
        }
        else {

            cout << "Would you like to" << endl;
            cout << "1- Choose a webpage to open" << endl;
            cout << "2- New search" << endl;
            cout << "3- Exit" << endl;
            cout << "Type in your choice:(please type 1,2 or 3) ";
        }
        cin >> choice;
        if (choice == 1)
        {
            int WebsiteChoice;
            cout << "Choose a website! \n";
            cin >> WebsiteChoice;
            if (WebsiteChoice <= 0 || WebsiteChoice > relevantPages.size())
                cout << "wrong entry!" << endl;
            else {
                cout << "\n You're now viewing " << relevantPages[WebsiteChoice - 1].getlink() << endl;
                for (int i = 0; i < numberOFwebpages; i++)
                {
                    if (relevantPages[WebsiteChoice - 1].getPageNum() == pages[i].getPageNum())
                    {
                        pages[i].changeClickNum();
                        //updating files
                        printData(pages, numberOFwebpages);
                    }
                }
            }
            display2(relevantPages, pages, numberOFwebpages);
        }
        if (choice == 2)
        {
            ProcessSearcch(pages, numberOFwebpages);
        }
        if (choice == 3)
            exit(0);
    }

    if (AND == true && OR == false && quote == false)
    {
        // case of and 
        stringstream split(searchEntry);
        vector<string> keyWords;
        vector<string> searchkeyWords;
        keyWords.resize(0);
        searchkeyWords.resize(0);
        vector<webpage> relevantPages;
        relevantPages.resize(0);;
        vector<double> scores;

        while (split.good())
        {
            string temp;
            getline(split, temp, ' ');
            if (temp != "AND" && temp != "and")
            {
                searchkeyWords.push_back(temp);
            }
        }


        for (int i = 0; i < numberOFwebpages; i++)
        {
            keyWords = pages[i].getkeywords();
            int counter = 0;
            for (int j = 0; j < searchkeyWords.size(); j++)
            {
                for (int k = 0; k < keyWords.size(); k++)
                {
                    if (keyWords[k] == searchkeyWords[j])
                    {
                        counter++;
                        if (counter == searchkeyWords.size())
                        {
                            double x = pages[i].getPagescore();
                            scores.push_back(x);
                        }
                    }
                }

            }

        }
        mergeSort(scores, 0, scores.size() - 1); // we sort scores to be able to remove dupilicates
        removeDuplicates(scores, scores.size()); //now we have all the relevant webages to the search query, we need to sort page scores 
        for (int i = 0; i < scores.size(); i++)
        {
            for (int j = 0; j < numberOFwebpages; j++)
            {
                if (scores[i] == pages[j].getPagescore())
                {
                    relevantPages.push_back(pages[j]);
                    pages[j].changeImp();
                    // it will be displayed--> we need to change the number of impressions
                    //updating files
                    printData(pages, numberOFwebpages);
                }

            }
        }

        cout << "Here are the results for your search : " << endl;
        cout << "-------------------" << endl;
        for (int i = 0; i < relevantPages.size(); i++)
        {
            cout << i + 1 << "- " << relevantPages[i].getlink() << endl;

        }
        int choice;
        if (relevantPages.size() == 0)
        {
            cout << "No relevant Webpages!" << endl;
            cout << "Would you like to" << endl;
            cout << "2- New search" << endl;
            cout << "3- Exit" << endl;
        }
        else {

            cout << "Would you like to" << endl;
            cout << "1- Choose a webpage to open" << endl;
            cout << "2- New search" << endl;
            cout << "3- Exit" << endl;
            cout << "Type in your choice:(please type 1,2 or 3) ";
        }
        cin >> choice;
        if (choice == 1)
        {
            int WebsiteChoice;
            cout << "Choose a website! \n";
            cin >> WebsiteChoice;
            if (WebsiteChoice <= 0 || WebsiteChoice > relevantPages.size())
                cout << "wrong entry!" << endl;
            else {
                cout << "\n You're now viewing " << relevantPages[WebsiteChoice - 1].getlink() << endl;
                for (int i = 0; i < numberOFwebpages; i++)
                {
                    if (relevantPages[WebsiteChoice - 1].getPageNum() == pages[i].getPageNum())
                    {
                        pages[i].changeClickNum();
                        //updating files
                        printData(pages, numberOFwebpages);
                    }
                }
            }
            display2(relevantPages, pages, numberOFwebpages);
        }
        if (choice == 2)
        {
            ProcessSearcch(pages, numberOFwebpages);
        }
        if (choice == 3)
            exit(0);
    }
    if (AND == false && OR == true && quote == false)
    {
        // case of and 
        stringstream split(searchEntry);
        vector<string> keyWords;
        vector<string> searchkeyWords;
        keyWords.resize(0);
        searchkeyWords.resize(0);
        vector<webpage> relevantPages;
        relevantPages.resize(0);;
        vector<double> scores;

        while (split.good())
        {
            string temp;
            getline(split, temp, ' ');
            if (temp != "OR" && temp != "or")
            {
                searchkeyWords.push_back(temp);
            }
        }


        for (int i = 0; i < numberOFwebpages; i++)
        {
            keyWords = pages[i].getkeywords();
            for (int j = 0; j < searchkeyWords.size(); j++)
            {
                for (int k = 0; k < keyWords.size(); k++)
                {
                    if (keyWords[k] == searchkeyWords[j])
                    {
                        double x = pages[i].getPagescore();
                        scores.push_back(x);
                    }
                }

            }

        }
        mergeSort(scores, 0, scores.size() - 1); // we sort scores to be able to remove dupilicates
        removeDuplicates(scores, scores.size()); //now we have all the relevant webages to the search query, we need to sort page scores 
        for (int i = 0; i < scores.size(); i++)
        {
            for (int j = 0; j < numberOFwebpages; j++)
            {
                if (scores[i] == pages[j].getPagescore())
                {
                    relevantPages.push_back(pages[j]);
                    pages[j].changeImp();
                    // it will be displayed--> we need to change the number of impressions
                    //updating files
                    printData(pages, numberOFwebpages);
                }

            }
        }

        cout << "Here are the results for your search : " << endl;
        cout << "-------------------" << endl;
        for (int i = 0; i < relevantPages.size(); i++)
        {
            cout << i + 1 << "- " << relevantPages[i].getlink() << endl;

        }
        int choice;
        if (relevantPages.size() == 0)
        {
            cout << "No relevant Webpages!" << endl;
            cout << "Would you like to" << endl;
            cout << "2- New search" << endl;
            cout << "3- Exit" << endl;
        }
        else {

            cout << "Would you like to" << endl;
            cout << "1- Choose a webpage to open" << endl;
            cout << "2- New search" << endl;
            cout << "3- Exit" << endl;
            cout << "Type in your choice:(please type 1,2 or 3) ";
        }
        cin >> choice;
        if (choice == 1)
        {
            int WebsiteChoice;
            cout << "Choose a website! \n";
            cin >> WebsiteChoice;
            if (WebsiteChoice <= 0 || WebsiteChoice > relevantPages.size())
                cout << "wrong entry!" << endl;
            else {
                cout << "\n You're now viewing " << relevantPages[WebsiteChoice - 1].getlink() << endl;
                for (int i = 0; i < numberOFwebpages; i++)
                {
                    if (relevantPages[WebsiteChoice - 1].getPageNum() == pages[i].getPageNum())
                    {
                        pages[i].changeClickNum();
                        //updating files
                        printData(pages, numberOFwebpages);
                    }
                }
            }
            display2(relevantPages, pages, numberOFwebpages);
        }
        if (choice == 2)
        {
            ProcessSearcch(pages, numberOFwebpages);
        }
        if (choice == 3)
            exit(0);
    }
    if (AND == false && OR == false && quote == true)
    {
        // case of quotation

        searchEntry = searchEntry.substr(1, searchEntry.size() - 2); //removing quotation marks
        // all will be processed as one string
        vector<string> keyWords;
        keyWords.resize(0);
        vector<webpage> relevantPages;
        relevantPages.resize(0);;
        vector<double> scores;


        for (int i = 0; i < numberOFwebpages; i++)
        {
            keyWords = pages[i].getkeywords();
            for (int k = 0; k < keyWords.size(); k++)
            {
                if (keyWords[k] == searchEntry)
                {
                    double x = pages[i].getPagescore();
                    scores.push_back(x);
                }
            }



        }
        mergeSort(scores, 0, scores.size() - 1); // we sort scores to be able to remove dupilicates
        removeDuplicates(scores, scores.size());
        for (int i = 0; i < scores.size(); i++)
        {
            for (int j = 0; j < numberOFwebpages; j++)
            {
                if (scores[i] == pages[j].getPagescore())
                {
                    relevantPages.push_back(pages[j]);
                    pages[j].changeImp();
                    // it will be displayed--> we need to change the number of impressions
                    //updating files
                    printData(pages, numberOFwebpages);
                }

            }
        }

        cout << "Here are the results for your search : " << endl;
        cout << "-------------------" << endl;
        for (int i = 0; i < relevantPages.size(); i++)
        {
            cout << i + 1 << "- " << relevantPages[i].getlink() << endl;

        }
        int choice;
        if (relevantPages.size() == 0)
        {
            cout << "No relevant Webpages!" << endl;
            cout << "Would you like to" << endl;
            cout << "2- New search" << endl;
            cout << "3- Exit" << endl;
        }
        else {

            cout << "Would you like to" << endl;
            cout << "1- Choose a webpage to open" << endl;
            cout << "2- New search" << endl;
            cout << "3- Exit" << endl;
            cout << "Type in your choice:(please type 1,2 or 3) ";
        }
        cin >> choice;
        if (choice == 1)
        {
            int WebsiteChoice;
            cout << "Choose a website! \n";
            cin >> WebsiteChoice;
            if (WebsiteChoice <= 0 || WebsiteChoice > relevantPages.size())
                cout << "wrong entry!" << endl;
            else {
                cout << "\n You're now viewing " << relevantPages[WebsiteChoice - 1].getlink() << endl;
                for (int i = 0; i < numberOFwebpages; i++)
                {
                    if (relevantPages[WebsiteChoice - 1].getPageNum() == pages[i].getPageNum())
                    {
                        pages[i].changeClickNum();
                        //updating files
                        printData(pages, numberOFwebpages);
                    }
                }
            }
            display2(relevantPages, pages, numberOFwebpages);
        }
        if (choice == 2)
        {
            ProcessSearcch(pages, numberOFwebpages);
        }
        if (choice == 3)
            exit(0);

    }





}




int main()
{

    vector<webpage>webpages;
    int numofwebpages = InitializeWebpages(webpages);
    linkPages(webpages, numofwebpages);
    calculatePageRank(webpages, numofwebpages);
    /*for (int i = 0; i < numofwebpages; i++)
        webpages[i].printWebpage();*/
    int number;
    string entry;
    cout << "Welcome ! " << endl;
    cout << "What would you like to do ? " << endl;
    cout << "1. New search " << endl;
    cout << "2. Exit " << endl;
    cout << endl;
    cout << "Type in your choice (type either 1 or 2) : ";
    cin >> number;
    if (number == 1)
    {
        ProcessSearcch(webpages, numofwebpages);
    }
    if (number == 2)
        return 0;

}

