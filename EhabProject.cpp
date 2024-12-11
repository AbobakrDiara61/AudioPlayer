/*
    ---> This is to view the input Devices but is a vector didn't study and understand <---

              vector<string> availableDevices = SoundRecorder::getAvailableDevices();
              for (int i = 0; i < availableDevices.size(); i++)
              {
                  cout << availableDevices.at(i) << endl;
              }

              string inputDevice = availableDevices[0];
              SoundBufferRecorder recorder2;
              if (!recorder.setDevice(inputDevice))
              {
                  cout << "Error: Problem Setting Recording Device" << endl;
              }
              }
    */

#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include <string>
#include <cstring>
// for map
#include<map>
#include <iomanip>
// for time
#include <ctime>
class Date
{
protected:
    tm localDate;
    int day, month, year;
public:
    // Constructor to initialize the date
    Date()
    {
        time_t now = time(0);           // Get current time
        tm localDate;                   // Local time structure
        localtime_s(&localDate, &now);  // Populate localDate with the current time

        day = localDate.tm_mday;        // Extract the current day
        month = localDate.tm_mon + 1;   // Extract the current month (0-based)
        year = 1900 + localDate.tm_year;// Extract the current year
    }
    // Constructor for user-specified date
    Date(int day, int month, int year) {
        if (isValidDate(day, month, year)) {
            this->day = day;
            this->month = month;
            this->year = year;
        }
        else {
            std::cerr << "Invalid date! Setting to default (01/01/2000)." << std::endl;
            this->day = 1;
            this->month = 1;
            this->year = 2000;
        }
    }
    // Helper function to validate the date
    bool isValidDate(int day, int month, int year) {
        if (year < 1 || month < 1 || month > 12 || day < 1) {
            return false;
        }
        // Days in each month
        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        // Adjust for leap years
        if (month == 2 && isLeapYear(year)) {
            daysInMonth[1] = 29;
        }

        return day <= daysInMonth[month - 1];
    }
    // Helper function to check for leap year
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    // Print the date in DD/MM/YYYY format
    void print() {
        std::cout << (day < 10 ? "0" : "") << day << "/"
            << (month < 10 ? "0" : "") << month << "/"
            << year << std::endl;
    }
};
float clamp(float value, float min, float max) {
    if (value > max) return max;
    else if (value < min) return min;
    return value;
}
class AudioDetails {
private:
    // still need dates
    Date publishedDate; // Date Done
    std::string filePath;
    std::string fileName;
    float volume = 100.0f;
    float duration = 0.0f;
    float speed = 1.0f;

public:
    AudioDetails(const std::string& name, const std::string& path, float V, float D, float speed) { // looping it in a method in LL for make our LL intilized
        this->fileName = name;
        this->filePath = path;
        this->duration = D;
        this->volume = V;
        this->speed = speed;
    }/*
    AudioDetails(sf::Music audioFile,std::string& path) {

    }
     */
    AudioDetails() { // Default constructor for checking if he didn't sign any data
        this->filePath = "Empty";
        this->fileName = "Empty";
    }

    // ================== Setters ==================
    void setFilName(std::string fileName) { this->fileName = fileName; }
    void setFilePath(std::string filePath) { this->filePath = filePath; }
    void setVolume(float volume) { this->volume = volume; }
    void setDuration(float duration) { this->duration = duration; }
    void setSpeed(float) { this->speed = speed; }
    // ================== Getters ==================
    std::string getFilName() { return fileName; }
    std::string getFilePath() { return filePath; }
    float getVolume() { return volume; }
    float getDuration() { return duration; }
    float getSpeed() { return speed; }

    void printDetails() {
        std::cout << "File Name: " << fileName << "\t"
            << "Path: " << filePath << "\n"
            << "Duration: " << duration << "\t"
            << "Speed: " << speed << "\t"
            << "Volume: " << volume << "\n";
    }
};

class AudioNode {
public:
    AudioDetails audioDetails;
    AudioNode* next;

    AudioNode(AudioDetails audioDetails) {
        this->audioDetails = audioDetails;
        next = nullptr;
    }
};
class LinkedList {
private:
    AudioNode* head;
    AudioNode* tail;
    int length;
public:
    LinkedList(AudioDetails audioDetails) { // check the another constructor doesn't effect this
        AudioNode* newAudioNode = new AudioNode(audioDetails);
        head = newAudioNode;
        tail = newAudioNode;
        length = 1;
    }
    LinkedList() {
        head = tail = nullptr;
        length = 1;
    }
    ~LinkedList() {
        AudioNode* temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }
    void Append(AudioDetails audioDetails) {
        AudioNode* newAudioNode = new AudioNode(audioDetails);
        if (length == 0) {
            head = newAudioNode;
            tail = newAudioNode;
        }
        else {
            tail->next = newAudioNode;
            tail = newAudioNode;
        }
        length++;
    }
    void deleteLast() {
        if (length == 0) { return; }
        AudioNode* temp = head;
        AudioNode* pre = head;
        while (temp->next) {
            pre = temp;
            temp = temp->next;
        }
        tail = pre;
        tail->next = nullptr;
        length--;
        if (length == 0) {
            /* delete head; kda kda temp points to it*/
            head = tail = nullptr;
        }
        delete temp;
    }
    void prepend(AudioDetails audioDetails) {
        AudioNode* newAudioNode = new AudioNode(audioDetails);
        if (length == 0) {
            head = newAudioNode;
            tail = newAudioNode;
        }
        else {
            newAudioNode->next = head;
            head = newAudioNode;
        }
    }
    void deleteFirst() {
        if (length == 0) { return; }
        AudioNode* temp;
        temp = head;
        if (length == 1) {
            head = nullptr;
            tail = nullptr;
        }
        else {
            head = head->next;
        }
        delete temp;
        length--;
    }
    AudioNode* get(int index) {
        if (index >= length || index < 0) return nullptr;
        AudioNode* temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp;

    }
    bool set(int index, AudioDetails audioDetails) {
        AudioNode* temp = get(index);
        if (temp) {
            temp->audioDetails = audioDetails;
            return true;
        }
        return false;
    }
    bool insert(int index, AudioDetails audioDetails) {
        if (index<0 || index > length) return false;
        if (index == 0) {
            prepend(audioDetails);
            return true;
        }
        if (index == length) {
            Append(audioDetails);
            return true;
        }
        AudioNode* newAudioNode = new AudioNode(audioDetails);
        AudioNode* temp = get(index - 1);
        newAudioNode->next = temp->next;
        temp->next = newAudioNode;
        length++;
        return true;
    }
    void deleteAudioNode(int index) {
        if (index == 0) return deleteFirst();
        if (index == length - 1) return deleteLast();  /* {deleteLast();} so no need for elseIf */
        AudioNode* prev = get(index - 1);
        AudioNode* temp = prev->next; // it's not efficient to use get(index)
        prev->next = temp->next;
        delete temp;
        length--;
    }
    void printLinkedList() {
        AudioNode* temp = head;
        while (temp)
        {
            temp->audioDetails.printDetails();
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};
class AudioPlayer {
    AudioDetails detailsHandler;
    sf::Sound sound;
    sf::SoundBuffer buff;
    sf::Music audioFile;
    sf::Keyboard::Key k;
    sf::Event event;
public:
    bool loadAudioFile(const std::string& fileName) {
        if (audioFile.openFromFile(fileName) == false) {
            //   std::cerr << "Error Opening the file plz check the correct path\n"; in main we can make the output to choose another file
            return false;
        }
        return true;
    }

    bool display(const std::string& inputPath) {
        bool isPaused = false;
        // audioFile.openFromFile(inputPath);
       //  std::cout << "Playing an audio:\n";
        std::cout << "Audio Player Controls:\n"
            << "P: Play\n"
            << "S: Stop\n"
            << "Space: Pause/Resume\n"
            << "Up: Increase the volume\n"
            << "Down: Decrease the volume\n"
            << "V: Set the volume\n"
            << "A: Speed The audio\n"
            << "D: Slow The audio\n"
            << "Y: Set a specific speed for The audio\n"
            << "Right: Offset the audio 5 seconds forward\n"
            << "Left: Offset the audio 5 seconds backward\n"
            << "V: Start the audio at specific second\n"
            << "Escape: Quit\n";
        // Keys for setting the loop

        while (true)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                audioFile.play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                std::cout << "S key pressed stoping the audio \n";
                audioFile.stop();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                std::cout << "Escape key pressed. Exiting...\n";
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (audioFile.getStatus() == sf::Music::Playing)
                    audioFile.pause();
                else audioFile.play();
                sf::sleep(sf::milliseconds(100));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                // you should put in it the same file path then from the start you didn't make the constructor for this class you can other classes
                //detailsHandler.printDetails(); 
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                setVolume();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                setVolume(false);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
                float temp;
                std::cout << "Enter The Volume:\n";
                std::cin >> temp;
                setVolume(temp);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { ; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { ; }

            sf::sleep(sf::milliseconds(100));
        }
        return 1;
    }
    void setVolume(float volume = 5.0f, bool isIncreasing = true) {
        // if (detailsHandler.getVolume() <= 0.0f && detailsHandler.getVolume() >= 100.0f) return; will make the volume remain the same
        float currentVolume = detailsHandler.getVolume();
        std::cout << "Current Volume: " << currentVolume << "\n"; // Debug info
        if (volume == 5.0f) {
            if (isIncreasing)
                // Increase volume by 5.0f, capped at 100.0f
                audioFile.setVolume(std::min(currentVolume + volume, 100.0f));
            else if (!isIncreasing)
                // Decrease volume by 5.0f, capped at 0.0f
                audioFile.setVolume(std::max(currentVolume - volume, 0.0f));
        }
        else
            audioFile.setVolume(clamp(volume, 0.0f, 100.0f)); //do the clamp check the logic
        // Update the details handler to reflect the new volume
        std::cout << "Current Volume: " << audioFile.getVolume() << "\n"; // Debug info
        detailsHandler.setVolume(audioFile.getVolume());
    }

};
// Before this class we need in menu To choose if you want to open Audio or Record, After Recording it becames an Audio.
class AudioRecorder : public AudioPlayer, AudioDetails
{
private:
    sf::SoundBufferRecorder recorder;
    std::string OutputFile;   // For after record take the path or name and go to Audio player and play it.
    sf::SoundBuffer buffer;
    std::string savefilePath;
    std::string savefileName;
    bool isRecording;
public:
    AudioRecorder()
    {
        isRecording = false;
        savefilePath = "C:\\Users\\pc\\Downloads\\TestRecord.wav"; //This the default path to save file on it..
        savefileName = "TestRecord.wav";       // The default namefile
    }
    AudioRecorder(std::string Path, std::string filename)
    {
        this->isRecording = false;
        this->savefilePath = Path;
        this->savefileName = filename;
    }

    bool startRecording() {
        if (!sf::SoundBufferRecorder::isAvailable()) { //???
            std::cout << "Audio recording is not supported on this system.\n"; //cerr??
            return false;
        }

        // Check if the recorder is already recording
        if (isRecording) {
            std::cout << "Already recording. Stop the current recording before starting a new one.\n";  //cerr??
            return false;
        }
        else {
            std::cout << "Recording started. Press Enter to stop.\n";
            recorder.start();
            isRecording = true;
            return true;
        }
    }
    void stopRecording()
    {
        recorder.stop();
        buffer = recorder.getBuffer();
        // After getBuffer we need to print the "Recording Stopped!" and connect with class AudioPlayer. 
        saveRecording();
    }
    bool saveRecording()
    {
        if (buffer.saveToFile(savefilePath))
        {
            std::cout << "Recording save to : " << savefilePath << "\n";
            std::cout << "Recording file is : " << savefileName << "\n";
            return 1;
        }
        else
        {
            std::cout << "Failed to save the recording." << std::endl;  //cerr??
            return 0; // we cann use if condition in this line in the main
        }
    }

    // ================== Setters ==================
    void changeFilePath(std::string filePath) { this->savefilePath = filePath; }
    void changeFileName(std::string fileName) { this->savefileName = fileName; }
    // ================== Getters ==================
    std::string getFileName() { return savefileName; }
    std::string getFilePath() { return savefilePath; }
};

#include <iostream>
#include <cstring>
#include<map>

int main(void);

std::map<std::string, std::string>viewer_map = { {"test","test"} };
std::map < std::string, std::string > uploader_map = { {"test","test"} };//the two maps arent empty because we cannot loop through an empty map 

std::string username, password;

//user menu.
void User_menu(void/*int choice*/) {
    bool dataentered = false;
    int choice2;
    while (true) {
        std::cout << "\n\t\t\t\t\t============== User Menu ==============" << std::endl << std::endl;
        std::cout << "\t\t\t\t\t\t1.Upload Audio." << std::endl;
        std::cout << "\t\t\t\t\t\t2.Record Audio." << std::endl;
        std::cout << "\t\t\t\t\t\t3.Include Audio file." << std::endl;
        std::cout << "\t\t\t\t\t\t4.Edit spead." << std::endl;
        std::cout << "\t\t\t\t\t\t5.stop Audio." << std::endl;
        std::cout << "\t\t\t\t\t\t6.quite." << std::endl << std::endl;
        std::cout << "\t\t\t\t\t===================================" << std::endl;
    sine:
        std::cout << "choose number:" << std::endl;
        std::cin >> choice2;
        switch (choice2)
        {

        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: {std::cout << "Thank you for using our project :)\n";
            std::cout << "Exiting Program.";
            system("pause");
            main();
            break;}
        default: std::cout << "This is an invalid choice" << std::endl << "PLease Try Again" << std::endl << std::endl;goto sine;

        }
    }
}
//Uploder menu.
void Uploder_menu(void/*int choice*/) {
    bool dataentered = false;
    int choice;
    while (true) {
        std::cout << "Hello Admin!";
    signe:
        std::cout << "\n\t\t\t\t\t============= Uploder Menu =============" << std::endl << std::endl;
        //cout << "1.Creat user." << std::endl;
        std::cout << "\t\t\t\t\t\t1.Upload Audio." << std::endl;
        std::cout << "\t\t\t\t\t\t2.Record Audio." << std::endl;
        std::cout << "\t\t\t\t\t\t3.Include Audio file." << std::endl;
        std::cout << "\t\t\t\t\t\t4.Edit spead." << std::endl;
        std::cout << "\t\t\t\t\t\t5.Genrate Audio." << std::endl;
        std::cout << "\t\t\t\t\t\t6.stop Audio." << std::endl;
        std::cout << "\t\t\t\t\t\t7.quit." << std::endl << std::endl;
        std::cout << "\t\t\t\t\t========================================" << std::endl;
        std::cout << "choose number:" << std::endl;
        std::cin >> choice;

        switch (choice)
        {
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        case 7: {std::cout << "Thank you for using our project :)\n";
            std::cout << "Exiting Program.";
            system("pause");
            main();
            break;}
        default: std::cout << "This is an invalid choice \n Please try again. \n \n";goto signe;

        }
    }
}
// User class
class User {

protected:
    std::string name, pass;
public:

    void setName(std::string username) { name = username; }
    void setPass(std::string password) { pass = password; }

    bool viewer;
    std::string getName() { return name; }
    std::string getPass() { return pass; }


    void Login(void)
    {
        int choice;
        bool login_succeded = false;
        std::string username, password;
    sf4:std::cout << "Welcome to Login page\nplease enter your username and password \n";
        std::cout << "username : ";
        std::cin >> username;
        std::cout << "password : ";
        std::cin >> password;
        if (viewer) {
            login_succeded = search(viewer_map, username, password);
        }
        else { login_succeded = search(uploader_map, username, password); }
        if (login_succeded)
        {
            std::cout << "login succeded ";//function to throw to menu
            if (viewer) { User_menu(); }
            else Uploder_menu();
        }
        else
        {
        sf5:  std::cout << "login failed \n1.try again\n2.sign up";
            std::cin >> choice;
            if (choice == 1) { goto sf4; }
            else if (choice == 2) { Sign_UP(); }
            else { std::cout << "invalid input";goto sf5; }
        }
    }

    void Sign_UP(void)
    {
    sf3:std::cout << "welcom to Sign_UP page\nplease enter your username and password \n";
        std::cout << "username : ";
        std::cin >> username;
        std::cout << "password : ";
        std::cin >> password;
        if (viewer) {
            if (check_username(viewer_map, username)) { viewer_map.insert({ username,password });User_menu(); }
            else { std::cout << "username is already taken please pick another one";goto sf3; }
        }
        else {
            if (check_username(uploader_map, username)) { uploader_map.insert({ username,password });Uploder_menu(); }
            else { std::cout << "username is already taken please pick another one";goto sf3; }
        }
        //function to make user go to menu

    }
    bool search(std::map<std::string, std::string>& map, std::string username, std::string password)
    {
        for (auto a : map)
        {
            if (a.first == username && a.second == password) { std::cout << "FOUND ";return true; }
            else std::cout << "NOT FOUND";
        }
        return false;
    }
    bool check_username(std::map<std::string, std::string>map, std::string username)
    {
        bool username_NotFound = true;
        for (auto a : map)
        {
            if (a.first == username) { return !username_NotFound; }
        }
        return username_NotFound;
    }
};

//uploader class
class Uploader :public User {
private:
    std::string link;

public:
    Uploader() { viewer = false; }
    /* Uploader() {
         name = "Admin";
         pass = "Admin";
     }*/
    void setLink(std::string linkpath) { link = linkpath; }
    std::string getLink() { return link; }

};

//Viewer class
class Viewer : public User {
public:Viewer() { viewer = true; }
};

/*if (choice == 6) {
    cout << "Thank you for using our project :)\n";
    cout << "Exiting Program.";
    system("pause");
    break;
}
else if (choice == 1) {

}
else if (choice == 2) {

}
else if (choice == 3) {

}
else if (choice == 4) {

}
else if (choice == 5) {

}
else {
    cout << "This Is Invaled Choice." << std::endl << "Please Try Again.\n\n";
    goto sine;
}*/




/*if (choice == 7) {
    cout << "Thank you for using our project :)\n";
    cout << "Exiting Program.";
    system("pause");
    break;
}
else if (choice == 1) {
}
else if (choice == 2) {

}
else if (choice == 3) {

}
else if (choice == 4) {

}
else if (choice == 5) {

}
else if (choice == 6) {

}
else {
    cout << "This Is Invaled Choice."<<std::endl<< "Please Try Again.\n\n";
    goto signe;
}*/




int main()
{
    Viewer v1;
    Uploader up;
    std::string name, pass;//Why do we need those. user,uploader and viewer classes already have their own name and pass
    int choice;
    bool test = 0;
    bool test_user = 0;


    while (true) {// I am not sure that this loop is correct so I comment it.
        std::cout << "\n\t\t\t\t_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n\n\n";
        std::cout << "\t\t\t\t            Welcome to the login page         \n\n\n";
        std::cout << "\t\t\t\t_ _ _ _ _ _ _ _ _     Menu    _ _ _ _ _ _ _ _ _ _ \n\n\n";
    label:     //this is for goto statment at line 81.
        std::cout << "\n\t| Press 1 to Login as a viewer        |" << std::endl;
        std::cout << "\t| Press 2 to Login as a uploader      |" << std::endl;
        std::cout << "\t| Press 3 to Exit                     |" << std::endl;
        std::cout << "\t Please enter your choice: ";
        std::cin >> choice;
        std::cout << "\n";
        system("cls");

        switch (choice)
        {
        case 1: v1.Login();
            break;
        case 2: up.Login();

        case 3: std::cout << "Thank you for using our project :)\n";
            std::cout << "Exiting Program.";
            system("pause");
            return 0;
        default:std::cout << "Your input is not valid\nPlease enter a valid input\n";
            std::cout << "enter your choice: ";//
            goto label;
            break;
        }
    }


}


// For learning the functions to write Audio Player code No need for it 
/*
    AudioPlayer p;
    std::string inputPath = "D:\\A\\aaa.wav";
    p.loadAudioFile(inputPath);
    p.display(inputPath);
    //p.display("D:\\A\\aaa.wav");
    sf::Music aud;
    aud.openFromFile("D:\\A\\aaa.wav");
    sf::Time period = aud.getDuration();
    for (int i = period.asSeconds(); i >= 0; i--) {
        std::cout << i << " ";
    }
    std::cout << period.asSeconds() << std::endl;
    float volume = aud.getVolume();
    std::cout << volume;
    aud.setVolume(50);
    volume = aud.getVolume();
    period = aud.getDuration();
    std::cout << "\nThe Volume now: " << volume << "\tThe Duration of Audio become: ";
    std::cout << period.asSeconds() << " seconds\n";

*/

/*
    sf::SoundBufferRecorder recorder;
    sf::SoundBuffer buffer;
    std::vector <std::string> availableDevices = sf::SoundBufferRecorder::getAvailableDevices();
    for (int i = 0; i < availableDevices.size(); i++)
        std::cout << availableDevices.at(i) << std::endl;
    if (!sf::SoundBufferRecorder::isAvailable())
        std::cerr << "Not Available\n";
    std::cout << "Press P to strat Recording\n"
        << "press F to stop Recording\n";
    while (true) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            recorder.start();

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            recorder.stop();
            break;
        }
    }
    buffer = recorder.getBuffer();
    buffer.saveToFile("Bakr.wav");
 */