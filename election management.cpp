#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Class to store Voter Information
class Voter {
public:
    string id;
    string name;
    int age;
    bool hasVoted;

    Voter(string voterId, string voterName, int voterAge) {
        id = voterId;
        name = voterName;
        age = voterAge;
        hasVoted = false;
    }
};

// Class to store Candidate Information
class Candidate {
public:
    string name;
    string party;
    int votes;

    Candidate(string candidateName, string candidateParty) {
        name = candidateName;
        party = candidateParty;
        votes = 0;
    }
};

// Class for managing the Election System
class Election {
private:
    vector<Voter> voters;
    vector<Candidate> candidates;
    bool votingOpen;

public:
    Election() {
        votingOpen = false;
    }

    // Add a new voter
    void addVoter() {
        string id, name;
        int age;
        cout << "Enter Voter ID: ";
        cin >> id;
        cout << "Enter Voter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Voter Age: ";
        cin >> age;

        for (const auto& voter : voters) {
            if (voter.id == id) {
                cout << "Voter with this ID already exists!\n";
                return;
            }
        }
        voters.push_back(Voter(id, name, age));
        cout << "Voter successfully registered!\n";
    }

    // Add a new candidate
    void addCandidate() {
        string name, party;
        cout << "Enter Candidate Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Candidate Party: ";
        getline(cin, party);

        candidates.push_back(Candidate(name, party));
        cout << "Candidate successfully registered!\n";
    }

    // Start the voting process
    void startVoting() {
        if (votingOpen) {
            cout << "Voting is already open!\n";
            return;
        }
        votingOpen = true;
        cout << "Voting has been opened!\n";
    }

    // Close the voting process
    void closeVoting() {
        if (!votingOpen) {
            cout << "Voting is already closed!\n";
            return;
        }
        votingOpen = false;
        cout << "Voting has been closed!\n";
    }

    // Cast a vote
    void castVote() {
        if (!votingOpen) {
            cout << "Voting is not open right now!\n";
            return;
        }
        string voterId;
        cout << "Enter your Voter ID: ";
        cin >> voterId;

        auto voterIt = find_if(voters.begin(), voters.end(), [&](Voter& v) {
            return v.id == voterId;
        });

        if (voterIt == voters.end()) {
            cout << "Voter not found!\n";
            return;
        }

        if (voterIt->hasVoted) {
            cout << "You have already voted!\n";
            return;
        }

        cout << "Candidates:\n";
        for (int i = 0; i < candidates.size(); i++) {
            cout << i + 1 << ". " << candidates[i].name << " (" << candidates[i].party << ")\n";
        }

        int candidateChoice;
        cout << "Enter the candidate number you want to vote for: ";
        cin >> candidateChoice;

        if (candidateChoice < 1 || candidateChoice > candidates.size()) {
            cout << "Invalid candidate selection!\n";
            return;
        }

        candidates[candidateChoice - 1].votes++;
        voterIt->hasVoted = true;

        cout << "Vote successfully cast!\n";
    }

    // Show the election result
    void showResults() {
        if (votingOpen) {
            cout << "Voting is still ongoing. Please close voting to see results.\n";
            return;
        }

        cout << "Election Results:\n";
        for (const auto& candidate : candidates) {
            cout << candidate.name << " (" << candidate.party << ") - Votes: " << candidate.votes << "\n";
        }

        auto winnerIt = max_element(candidates.begin(), candidates.end(), [](Candidate& a, Candidate& b) {
            return a.votes < b.votes;
        });

        cout << "\nWinner: " << winnerIt->name << " from " << winnerIt->party << " with " << winnerIt->votes << " votes!\n";
    }
};

// Main Menu for election system
int main() {
    Election election;
    int choice;

    while (true) {
        cout << "\n--- Election Management System ---\n";
        cout << "1. Register a Voter\n";
        cout << "2. Register a Candidate\n";
        cout << "3. Open Voting\n";
        cout << "4. Cast a Vote\n";
        cout << "5. Close Voting\n";
        cout << "6. Show Election Results\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            election.addVoter();
            break;
        case 2:
            election.addCandidate();
            break;
        case 3:
            election.startVoting();
            break;
        case 4:
            election.castVote();
            break;
        case 5:
            election.closeVoting();
            break;
        case 6:
            election.showResults();
            break;
        case 7:
            cout << "Exiting the system...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
