#include<iostream>
#include <fstream>//file handling related
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<conio.h>
#include<ios>	// for <streamsize>
#include<limits> // for numeric_limits

using namespace std;
void eraseFileLine(string, string,string = "");
class Blog_Management_System
{
    private :
    string userName, passWord;
    string authorName, category, blogTitle, blog;
    public:
        void menu();
        bool RegisterId();
        string LoginId();

        void WriteBlog();
        void UpdateBlog();
        void SearchBlog();
        void DeleteBlog();
        void Delete(int,string);
        void Update(int,string);
        void BlogList();
        void ReadBlog(int);


};

void Blog_Management_System :: BlogList()
{
    system("cls");
    cout << "\t\t\t--------------------------" << endl;
    cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
    cout << "\t\t\t--------------------------" << endl<<endl<<endl;
    fstream file;
    string BlogFile;
    int choice;

    file.open("0 BLOG_LIST.txt", ios::in);//open file for read operations
    bool isEmpty = file.peek() == EOF;//checks if next character is EOF or not

    if(!file || isEmpty)
    {
        cout<<"\n\nNo Blogs Available Right Now";
        cout<<"\n\nKindly visit after sometime.\n";
        cout<<"\nPress any key to exit.\n";
        getch();
        exit(0);
    }
    else
    {
        int i=1;
        while (!file.eof() )
        {
            getline(file,BlogFile);
            getline(file,userName);
            if(BlogFile=="")
            break;
            cout<<i<<". "<<BlogFile<<endl;
            i++;

        }
        file.close();

        cout<<endl<<"Press 1/2/3..... to read blog:- ";
        cin>>choice;
        if(choice<i && choice !=0)
        ReadBlog(choice);
        else
        {
            cout<<"\n\n-->Wrong Choice";
            cout<<"\n\nPress Any Key To Continue-> ";
            getch();
            menu();
        }
    }
}

void Blog_Management_System :: ReadBlog(int choice)
{
    Blog_Management_System obj;
    fstream file;
    int i=1;
    string line;
    file.open("0 BLOG_LIST.txt", ios::in);
    while(i<=choice) // to get specific blog name
    {
        getline(file,blogTitle);
        getline(file,userName);

        i++;
    }
    file.close();

    file.open(userName+"- "+blogTitle+".txt", ios::in);
    if(!file)
    {
        cout<<"\nBlog is empty";
        cout<<"\n\nKindly read any other blog."<<endl;
    }
    else
    {
        system("cls");
        cout << "\t\t\t--------------------------" << endl;
        cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
        cout << "\t\t\t--------------------------" << endl;
        cout<<endl;
        cout<<"Blog Title  :- "<<blogTitle<<"\n\n";
        cout<<"Author Name :- ";
        getline(file,line);
        cout<<line<<"\n\n";

        cout<<"Category    :- ";
        getline(file,line);
        cout<<line<<"\n\n";

        cout<<"-->> ";
        getline(file,line);

        if(line=="")
        cout<<"No Content Available.";
        else
        {
            while(!file.eof() )
            {
                cout<<line<<endl;
                cout<<"     ";
                getline(file, line);

            }
        }
    }
    cout<<"\n\n->Press Any Key To Go Main Menu-- ";
    getch();
    menu();


}

void Blog_Management_System :: WriteBlog()
{
    bool b;
    fstream file;
    logIN:
    system("cls");
    cout << "\t\t\t--------------------------" << endl;
    cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
    cout << "\t\t\t--------------------------" << endl;
    cout<<"\n\n\t\t\tTO WRITE BLOG USER MUST LOGIN";
    cout<<"\n\n1. Already have account : Login";
    cout<<"\n2. Create account       : Sign up";
    cout<<"\n3. Main Menu";
    int choice;
    cout<<"\n\nEnter Your Choice:- ";
    cin>>choice;

    string user;

    switch(choice)
    {
        case 1: user = LoginId();
                break;
        case 2: b=RegisterId();
                if(b==true)
                {
                    cout<<"\nAccount Created\n";
                    cout<<"\nPress any key to continue:- ";
                    getch();
                    goto logIN;

                }
                else
                {
                cout<<"\nPress any key--";
                getch();
                goto logIN;
                }
                break;
        case 3: menu();
                break;
        default:
                cout<<"Wrong choice";
                cout<<"\nPress any key to continue->";
                getch();
                goto logIN;
    }
    if(user==" ")
    {
    cout<<"\nLogin Failed\n";
    cout<<"\nPress any key to continue->";
    getch();
    goto logIN;
    }
    else
    {
        cout<<"\nLogin Sucessfull";
        cout<<"\n\nPress any key to continue-";
        getch();

        system("cls");
        cout << "\t\t\t--------------------------" << endl;
        cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
        cout << "\t\t\t--------------------------" << endl;

        fstream blogs;
        fstream userblog;
        string blogTitle;

        cout<<"\n\nWRITE YOUR BLOG->\n";
        cout<<"-----------------";
        cout<<"\n\n->Enter the Blog Title:- ";
        cin.ignore();
        getline(cin, blogTitle);

        if(blogTitle=="")   //if blog title is empty. then no file will be created.
        {
            cout<<"\nWarning : Blog must have a Title.\n";
            cout<<"---------------------------------";
            cout<<"\n\nBlog is not saved\n";
            cout<<"\n\nPress any key to return main menu.";
            getch();
            menu();
        }

        file.open(user+"- "+blogTitle+".txt", ios::out);

        if(!file)
        {
            cout<<"\nUnable to write Blog due to file is not created\n\n";  // go for exit part if it execute.
            cout<<"Press any key to exit";
            getch();
            file.close();
            blogs.close();
            userblog.close();
            getch();
            exit(0);
        }
        else
        {
            blogs.open("0 BLOG_LIST.txt", ios::app | ios:: out);
            userblog.open(user+"'s BLOG.txt", ios::app | ios:: out);
            userblog<<blogTitle<<endl; // maintaing record via author wise
            blogs<<blogTitle<<endl<<user<<endl; //maintaing all blog list.
            userblog.close();
            blogs.close();
            //system("cls");
            //cout<< blog heading display;
            cout<<"\n->Enter Author Name:- ";
            getline(cin,authorName);

            if(authorName=="")      //if user has not given any author name.
            authorName="Unknown";

            file<<authorName<<endl; // writing author name into blog
            cout<<"\n->Enter Blog Category:- ";

            getline(cin,category);

            if(category=="")        // if user has not given any category then consider as others.
            category="Others";

            file<<category<<endl; // writing category into blog
            cout<<"\nNote 1. Press Enter Once  -> To Line Break";
            cout<<"\nNote 2. Press Enter Twice -> To Save Blog\n";
            cout<<"\n-----------------\n";
            cout<<"|  Start Typing |";
            cout<<"\n-----------------\n";
            cout<<"->";

            do
            {
                getline(cin, blog);
                file<<blog<<"\n";

            }while(blog!="");

            cout<<"\nBlog is saved";
            file.close();

        }
    }
    cout<<"\n\n->Press Any Key To Go Main Menu-- ";
    getch();
    menu();
}

void Blog_Management_System :: SearchBlog()
{
    system("cls");
    cout << "\t\t\t--------------------------" << endl;
    cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
    cout << "\t\t\t--------------------------" << endl;

    cout<<"\n\nSEARCH BLOGS (NOT CASE SENSITIVE) ->";
    cout<<"\n------------------------------------\n\n";
    string Blogname;
    fstream file;
    cin.ignore();
    cout<<"Enter the Blog Title To Search:- ";
    getline(cin,Blogname);
    if(Blogname!="")
        transform(Blogname.begin(), Blogname.end(), Blogname.begin(), ::toupper);
    else
    {
        cout<<"\n\n->Enter Proper Blog Title.";
        cout<<"\n\nPress any key to main menu-> ";
        getch();
        menu();
    }

    file.open("0 BLOG_LIST.txt", ios::in);
    int i=1,found=0;


    while(!file.eof())
    {
        getline(file,blogTitle);
        transform(blogTitle.begin(), blogTitle.end(), blogTitle.begin(), ::toupper);

        if(blogTitle==Blogname)
        {
            cout<<"\n\n\t\t\t\t->>BLOG FOUND<<-";
            file.close();
            found++;
            int ch;
            cout<<"\n\nPress 1. TO READ IT";
            cout<<"\nPress 2. MAIN MENU";
            cout<<"\n\nEnter Your Choice- ";
            cin>>ch;
            switch(ch)
            {
                case 1: ReadBlog(i);
                        break;

                case 2: menu();
                        break;
                default:
                        cout<<"\n\nWrong Input";
                        cout<<"\n\nPress Any Key To continue-";
                        getch();
                        menu();
            }
        }
        i++;


    }
    if(found==0)
    {
        cout<<"\n\n->BLOG NOT FOUND";
        cout<<"\n\nPress Any Key To Main Menu-";
        file.close();
        getch();
        menu();
    }
    file.close();
}

void Blog_Management_System :: DeleteBlog()
{
logIN:
    system("cls");
    cout << "\t\t\t--------------------------" << endl;
    cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
    cout << "\t\t\t--------------------------" << endl;

    cout<<"\n\n\t\t\t->TO DELETE BLOG USER MUST LOGIN<-";
    cout<<"\n----------------------------------";


    cout<<"\n\n1. Login";
    cout<<"\n2. Main Menu";

    int choice;
    cout<<"\n\nEnter Your Choice:- ";
    cin>>choice;

    string user;
    fstream file;

    switch(choice)
    {
        case 1: user = LoginId();
                break;
        case 2: menu();
                break;
        default:
                cout<<"\n\n->Wrong choice";
                cout<<"\n--------------";
                cout<<"\n\nPress any key to continue-> ";
                getch();
                goto logIN;
    }
    if(user==" ")
    {
    cout<<"\nLogin Failed\n";
    cout<<"\nPress any key to continue->";
    getch();
    goto logIN;
    }
    else
    {
        cout<<"\nLogin Sucessfull";
        cout<<"\n\nPress any key to continue-";
        getch();

        system("cls");
        cout << "\t\t\t--------------------------" << endl;
        cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
        cout << "\t\t\t--------------------------" << endl;

        cout<<"\n\n\t\t\t\t->DELETE BLOG<-";
        cout<<"\n\t\t\t\t---------------\n\n";

        file.open(user+"'s BLOG.txt", ios::in);

        bool isEmpty = file.peek() == EOF;
        if(!file || isEmpty)
        {
            cout<<"\n\nNo Blogs Available To Delete";
            cout<<"\n\nUnable To Delete.\n";
            cout<<"\nPress any key to main menu-\n";
            getch();
            menu();
        }
        else
        {
            int i=1;
            while (!file.eof() )
            {
                getline(file,blogTitle);
                if(blogTitle=="")
                break;
                cout<<i<<". "<<blogTitle<<endl;
                i++;

            }
            file.close();

            cout<<endl<<"Press 1/2/3..... to delete blog:- ";
            cin>>choice;

            if(choice<i)
            {
                 Delete(choice,user);
            }
            else
            {
                cout<<"\n\n-->Wrong Choice";
                cout<<"\n\nPress Any Key To Continue-> ";
                getch();
                menu();
            }
        }

    }
}

void Blog_Management_System :: Delete(int choice, string user)
{
    fstream file, file1;
    int i=1;
    file.open(user+"'s BLOG.txt", ios::in);
    while(i<=choice)
    {
        getline(file,blogTitle);
        i++;
    }
    file.close();

    string title;

     title= user+"- "+blogTitle+".txt";
    const char * ch= title.c_str();
    cout<<ch;
    int result = remove(ch);

    if(result==0)
    {
        cout<<"\n\n->BLOG DELETED";
    }
    else
    {
        cout<<"\n\n->FILE DOES NOT EXIST";
        cout<<"\n\nPress any key to main menu- ";
        getch();
        menu();
    }

    eraseFileLine(user+"'s BLOG",blogTitle);
    eraseFileLine("0 BLOG_LIST",blogTitle);
    cout<<"\n\nPress Any Key To Main Menu: ";
    getch();
    menu();
}

void eraseFileLine(string path, string eraseLine,string addLine)// erase a line and replace with other line.
{
    string line;
    fstream file,temp;
    path.append(".txt");
    file.open(path,ios::in);
    temp.open("temp.txt",ios::out);

    while (getline(file, line)) {
        // write all lines to temp other than the line marked for erasing
        if (line != eraseLine)
            temp<<line<<endl;
        else
            if(addLine == "");
            else
                temp<<addLine<<endl; //when line found replace it with other line.
    }

    temp.close();
    file.close();

    // required conversion for remove and rename functions
    const char * p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

void Blog_Management_System :: Update(int choice, string user)
{
    fstream file, file1,userBlog;
    string blog,line,tmpAuthorName,tmpBlogTitle,tmpCategory,tmpBlog = "",tmp1,tmp2;
    int i=1,ch;
    file.open(user+"'s BLOG.txt", ios::in);
        while(i<=choice)
        {
            getline(file,blogTitle);
            i++;
        }
        file.close();
    Update:
        system("cls");
        cout << "\t\t\t--------------------------" << endl;
        cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
        cout << "\t\t\t--------------------------" << endl<<endl<<endl;
        cout<<"\n\n**Select Field To Update**\n\n";
        cout<<"\n1.Author Name";
        cout<<"\n2.Category";
        cout<<"\n3.Blog Title";
        cout<<"\n4.Blog";
        cout<<"\n5.Exit";
        cout<<"\n\nEnter your choice:-  ";
        cin>>ch;
        if(ch<=4 && ch>=1)
        {
            tmpBlogTitle = blogTitle;
            file.open(user+"- "+blogTitle+".txt",ios::in);
            file1.open("tmp.txt",ios::out);
            getline(file,tmpAuthorName);
            getline(file,tmpCategory);
            if(tmpBlog == ""){

                    while(getline(file,line)) // blog
                    {
                        line.append("\n");
                        tmpBlog += line;
                    }
            }

        }
        system("cls");
        cout << "\t\t\t--------------------------" << endl;
        cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
        cout << "\t\t\t--------------------------" << endl;
        cout<<endl;
        cout<<"Blog Title  :- "<<blogTitle<<"\n\n";
        cout<<"Author Name :- ";
        cout<<tmpAuthorName<<"\n\n";

        cout<<"Category    :- ";
        cout<<tmpCategory<<"\n\n";

        cout<<"-->> ";
        if(tmpBlog=="")
                cout<<"No Content Available.";
        else
            cout<<tmpBlog<<"\n";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        switch(ch){

            case 1:cout<<"\nEnter new author name:";
                   getline(cin,tmpAuthorName);
                   break;
            case 2:cout<<"\nEnter new category name:";
                   getline(cin,tmpCategory);
                   break;
            case 3:cout<<"\nEnter new blog title name:";
                   getline(cin,tmpBlogTitle);

                   break;
            case 4:cout<<"\nEnter new blog:";
                   cout<<"\nNote 1. Press Enter Once  -> To Line Break";
                   cout<<"\nNote 2. Press Enter Twice -> To Save Blog\n";
                   cout<<"\n-----------------\n";
                   cout<<"|  Start Typing |";
                   cout<<"\n-----------------\n";
                   cout<<"->";
                   tmpBlog = "";
                   blog = "";
                   do
                    {
                        getline(cin, blog);
                        tmpBlog +=blog;
                        tmpBlog;

                    }while(blog!="");

                    cout<<"\nBlog is saved";
                  break;
            case 5:return;

            default:cout<<"\nInvalid Choice";

        }

    file.close();
    file1<<tmpAuthorName<<"\n";
    file1<<tmpCategory<<"\n";

    file1<<tmpBlog<<"\n";
    file1.close();
    if(blogTitle != tmpBlogTitle){

    eraseFileLine("0 BLOG_LIST",blogTitle,tmpBlogTitle);
    //user.txt
    eraseFileLine(user+"'s BLOG",blogTitle,tmpBlogTitle);
    cout<<"\ndone";
    }
    tmp1 = user+"- "+blogTitle+".txt";
    //tmp1.append(".txt");
    remove(tmp1.c_str());
    tmp2 = user+"- "+tmpBlogTitle+".txt";
    //tmp2.append(".txt");
    if(rename("tmp.txt",tmp2.c_str()) == 0) cout<<"\nRenamed";

    cout<<"\n\n->>BLOG UPDATED";
    cout<<"\n\n->>Want To Update More Fields???\n\nPress 1 For Continue Update\nPress 0 To Main Menu\n\n";
    cout<<"Enter Your Choice:- ";
    cin>>ch;
    if(ch == 1)
    {
        blogTitle = tmpBlogTitle;
        goto Update;
    }
    else
    menu();
}

void Blog_Management_System :: UpdateBlog()
{
logIN:
    system("cls");
    cout << "\t\t\t--------------------------" << endl;
    cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
    cout << "\t\t\t--------------------------" << endl;

    cout<<"\n\n\t\t\t->TO UPDATE BLOG USER MUST LOGIN<-";
    cout<<"\n\t\t\t----------------------------------";


    cout<<"\n\n1. Login";
    cout<<"\n2. Main Menu";

    int choice;
    cout<<"\n\nEnter Your Choice:- ";
    cin>>choice;

    string user;
    fstream file;

    switch(choice)
    {
        case 1: user = LoginId();
                break;
        case 2: menu();
                break;
        default:
                cout<<"\n\n->Wrong choice";
                cout<<"\n--------------";
                cout<<"\n\nPress any key to continue-> ";
                getch();
                goto logIN;
    }
    if(user==" ")
    {
    cout<<"\nLogin Failed\n";
    cout<<"\nPress any key to continue->";
    getch();
    goto logIN;
    }
    else
    {
        cout<<"\nLogin Sucessfull";
        cout<<"\n\nPress any key to continue-";
        getch();

        system("cls");
        cout << "\t\t\t--------------------------" << endl;
        cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
        cout << "\t\t\t--------------------------" << endl;
        cout<<"\n\n\t\t\t\t->UPDATE BLOG<-";
        cout<<"\n\t\t\t\t---------------\n\n";

        file.open(user+"'s BLOG.txt", ios::in);

        bool isEmpty = file.peek() == EOF;
        if(!file || isEmpty)
        {
            cout<<"\n\nNo Blogs Available To Update";
            cout<<"\n\nUnable To Delete.\n";
            cout<<"\nPress any key to main menu-\n";
            getch();
            menu();
        }
        else
        {
            int i=1;
            while (!file.eof() )
            {
                getline(file,blogTitle);
                if(blogTitle=="")
                break;
                cout<<i<<". "<<blogTitle<<endl;
                i++;

            }
            file.close();

            cout<<endl<<"Press 1/2/3..... to delete blog:- ";
            cin>>choice;

            if(choice<i)
            {
                 Update(choice,user);

            }
            else{
                cout<<"\n\n-->Wrong Choice";
            cout<<"\n\nPress Any Key To Continue-> ";
            getch();
            menu();
        }
    }

    }
}

void Blog_Management_System :: menu()
{
        int choice;
        do
        {

        system("cls");

        cout << "\t\t\t--------------------------" << endl;
        cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
        cout << "\t\t\t--------------------------" << endl;
        cout<<"\t\t\t1. Read Blogs\n";
        cout<<"\t\t\t2. Write Blogs\n";
        cout<<"\t\t\t3. Update Blog\n";
        cout<<"\t\t\t4. Search Blog\n";
        cout<<"\t\t\t5. Delete Blog\n";
        cout<<"\t\t\t6. Exit";


        cout<<"\n\nEnter Your Choice:- ";
        cin>>choice;

        switch(choice)
        {
            case 1: BlogList();
                    break;
            case 2: WriteBlog();
                    break;
            case 3: UpdateBlog();
                    break;
            case 4: SearchBlog();
                    break;
            case 5: DeleteBlog();
                    break;
            case 6: exit(0);
            default:cout<<"\nInvalid Choice";
        }

    }while(choice<=6 && choice>=1);
}

bool Blog_Management_System :: RegisterId()
{
    system("cls");
    cout<< "\t\t\t--------------------------" << endl;
    cout<< "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
    cout<< "\t\t\t--------------------------" << endl;

    cout<<"\n\n\t\t\tCreate New Account ";
    cout<<"\n\nEnter the user name (NO Space Allowed) : - "; // space is not allowed in giving user name if space is entered the only string will be inputted befor space.
    cin>>userName;

    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    PASSWORD:
    cout<<"\nType 4 digit password: ";
    cin>>passWord;

    if(passWord.length() < 4 || passWord.length() >4)
    {
        goto PASSWORD;
    }

    fstream file;
    string tempUserName, tempPassWord;
    int found=0;
    file.open("0 LOGIN_DETAILS.txt",ios::in);
    if (!file) // if not created yet create login.txt file and enter the current user registration details.
    {
        file.close();
        file.open("0 LOGIN_DETAILS.txt", ios::out);
        file<<userName<<" "<<passWord<<endl;
        file.close();
        //cout<<"\nRegistered Successfully\n";
        cout<<"\n\n\t\t\tRegistered UserId:- "<<userName;
        cout<<"\n\t\t\tRegistered Password:- "<<passWord;
        return true;
    }
    else
    {
        while (!file.eof())
        {
            file >> tempUserName >> tempPassWord;
            if(userName == tempUserName)
            {
                found++;
                cout<<"\nUsername already Exist";
                cout<<"\n\n Registration Failed";
                file.close();
                return false;
            }
        }
        if(found == 0)
        {
            file.close();
            file.open("0 LOGIN_DETAILS.txt", ios::app | ios::out);
            file<<userName<<" "<<passWord<<endl;
            file.close();
            //cout<<"\nRegistered Successfully\n";
            cout<<"\n\n\t\t\tRegistered UserId:- "<<userName;
            cout<<"\n\t\t\tRegistered Password:- "<<passWord;
            return true;
        }
    }
    return 0;
}

string Blog_Management_System :: LoginId()
{
    system("cls");
    cout << "\t\t\t--------------------------" << endl;
    cout << "\t\t\t| BLOG MANAGEMENT SYSTEM |" << endl;
    cout << "\t\t\t--------------------------" << endl;

    cout<<"\nLOGIN CONSOLE->\n";
    cout<<"---------------\n";

    fstream file;
    string tempUserName, tempPassWord;
    int found=0;

    file.open("0 LOGIN_DETAILS.txt",ios::in);

    if (!file)
    {
        cout << "\n\n\t\t\tNo Data is Present. " << endl;
        cout<<"\nCreate new account First\n";
        file.close();
        return " " ;
    }
    else
    {
        cout<<"\nEnter username:- ";
        cin>>tempUserName;
        cout<<"\nEnter 4 Digit Password:- ";
        cin>>tempPassWord;

        while (!file.eof())
        {
            file >> userName >> passWord;

            if (userName == tempUserName)
            {
                found++;
                if(passWord == tempPassWord)
                {
                    file.close();
                    return userName;
                }
                else
                {
                    cout<<"\nWrong Password";
                    file.close();
                    return " ";
                }

            }
        }
        if (found == 0)
        {
            cout << "\nUser Does Not Exist";
            file.close();
            return " ";
        }
    }
    return 0;
}

int main()
{
    Blog_Management_System bobj;
    bobj.menu();
    return 0;

}
