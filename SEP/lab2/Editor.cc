#include <iostream>
#include <sstream>
#include "Editor.h"

using namespace std;

Editor::Editor()
{
    buffer = new Buffer();
}
Editor::~Editor()
{
    // TODO: Implement destructor
    buffer->list.clear();
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error &re) {
            cout << "? " << re.what() << endl;
        }
    }
}

void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        buffer->appendLine(text);
    }
    // TODO: finish cmdAppend.
}


void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    bool firstLine = true;
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        if (firstLine) {
            buffer->insertLine(text);
            firstLine = false;
        }  else {
            buffer->appendLine(text);
        }
    }
}

void Editor::cmdDelete(int start, int end)
{
    buffer->deleteLines(start, end);
}

void Editor::cmdNull(int line)
{
    cout << buffer->moveToLine(line) << endl;
}

void Editor::cmdNumber(int start, int end)
{
    buffer->showLines(start, end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if (cmd == "w") {
        cout<<"? Filename not specified"<<endl;
        return;
    }

    //使用适当的参数调用cmdWrite
    if (cmd[0] == 'w' && cmd[1] == ' ') {
        // TODO: call cmdWrite with proper arguments
        string name="";
        int i=2;
        while(cmd[i]){
            name.push_back(cmd[i]);
            i++;
        }

        if(name==""){
            cout<<"? Filename not specified"<<endl;
            return;
        }
        else{
            int num=(buffer->list.getbytes());
            cout<<num<<" byte(s) written"<<endl;
            return;
        }

    }

    // TODO: handle special case "1,$n".
    int start,end;
    char end1;
    char comma, type,type1,type2 = ' ';
    stringstream ss(cmd);
    stringstream other(cmd);
    ss >> start;
    other>>start;
    if (ss.eof()) {
        cmdNull(start);
        return;
    }


    ss >> comma >> end >> type1;
    other>> comma >> end1 >> type2;


    if(comma!=','){
        cout<<"? Bad/Unknown command"<<endl;
        return;
    }

    if(end1=='$'){
        end=buffer->list.size;
        type=type2;
    }
    else type=type1;

    if(start<1||end<start){
        if(type=='d')
            cout<<"? Delete range error"<<endl;
        else if(type=='n')
            cout<<"? Number range error"<<endl;
        else
            cout<<"? Bad/Unknown command"<<endl;
        return;
    }

    if(end>buffer->list.size){
        cout<<"? Line number out of range"<<endl;
        return;
     }

    if (ss.good()||other.good()) {
        if (type == 'n') {
            cmdNumber(start, end);
            return;
        } else if (type == 'd') {
            cmdDelete(start, end);
            return;
        }
        else {
            cout<<"? Bad/Unknown command"<<endl;
            return;
        }
    }

    throw "? Bad/Unknown command";
}
