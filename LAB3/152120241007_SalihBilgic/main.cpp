#include <iostream>
#include <string>

using namespace std;


struct Song {
    string title;
    string artist;
    int ratings[3];
    Song *next;
    Song *prev;
};

class Playlist {
private:
    Song *head;
    Song *tail;
    Song *current;

public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }


    void addSong(string songTitle, string songArtist, int songRatings[]) {
        Song *newSong = new Song;
        newSong->title = songTitle;
        newSong->artist = songArtist;

        for (int i = 0; i < 3; i++) {
            newSong->ratings[i] = songRatings[i];
        }

        newSong->next = nullptr;
        newSong->prev = nullptr;

        if (head == nullptr) {
            head = newSong;
            tail = newSong;
            current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
    }

    void nextSong() {
        if (current != nullptr && current->next != nullptr) {
            current = current->next;
        }
    }

    void prevSong() {
        if (current != nullptr && current->prev != nullptr) {
            current = current->prev;
        }
    }

    void removeCurrent() {
        if (current == nullptr) return;


        Song *target = current;

        if (target->prev != nullptr) {
            target->prev->next = target->next;
        } else {
            head = target->next;
        }

        if (target->next != nullptr) {
            target->next->prev = target->prev;
            current = target->next;
        } else {
            tail = target->prev;
            current = tail;
        }

        delete target;
    }

    void display() {
        if (head == nullptr) {
            cout << "\n[ Playlist is currently empty ]\n";
            return;
        }

        cout << "\n=== CURRENT PLAYLIST ===\n";


        for (Song *node = head; node != nullptr; node = node->next) {

            if (node == current) cout << "-> ";
            else cout << "   ";

            cout << node->title << " - " << node->artist << " | Scores: ";

            for (int i = 0; i < 3; i++) {
                cout << node->ratings[i] << (i < 2 ? ", " : "");
            }
            cout << "\n";
        }
        cout << "========================\n";
    }
};

int main() {
    Playlist myPlaylist;
    int option = -1;


    while (option != 0) {
        myPlaylist.display();

    cout << "\n1. Sarki ekle\n";
    cout << "2. Yeni sarkiya gec\n";
    cout << "3. Onceki Sarkiya Gec\n";
    cout << "4. Suanki Sarkiyi Kaldir\n";
    cout << "0. Cikis\n";
    cout << "Select an option: ";
    cin >> option;

    if (option == 1) {
        string titleInput, artistInput;
        int scoresInput[3];

        cout << "Song Title: ";
        cin.ignore();
        getline(cin, titleInput);

        cout << "Artist Name: ";
        getline(cin, artistInput);

        cout << "Enter 3 ratings (separated by space): ";
        cin >> scoresInput[0] >> scoresInput[1] >> scoresInput[2];

            myPlaylist.addSong(titleInput, artistInput, scoresInput);
        }
        else if (option == 2) {
            myPlaylist.nextSong();
        }
        else if (option == 3) {
            myPlaylist.prevSong();
        }
        else if (option == 4) {
            myPlaylist.removeCurrent();
        }
    }

    return 0;
}
