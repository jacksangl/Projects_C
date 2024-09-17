#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9
// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];
string preference[MAX_VOTERS][MAX_CANDIDATES];
int tracker;
int tracker2;
int done = 0;
int eliminated;

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// my variables
int maximum;
// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            preference[voter][rank] = name;
            return true;
        }
    }
    // rank += 1;
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int votes;
    int stopper;
    int flag;
    int max = candidate_count * voter_count;

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
              candidates[preferences[i][j]].votes += 1;
              j = candidate_count;
              break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{

    // done
    // done
    int winner = (voter_count / 2) + 1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= winner)
        {
            printf("%s\n", candidates[i].name);
            return true;
            break;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = MAX_VOTERS;
    int mincomp;
    tracker ++;
for (int i = 0; i < candidate_count; i++)
{
    if (candidates[i].eliminated == false)
    {
        mincomp = candidates[i].votes;
    }

    if (mincomp < min)
    {
        min = mincomp;
    }
}


return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int tie_guesser = 0;
    int tie = 0;
    int tied = 0;
    for (int i = 0; i < candidate_count; i++)
    {
            if (candidates[i].eliminated == false)
            {
                tied ++;
            }
    }


    // gets a candidate preference who isn't eliminated to serve as the benchmark for the tie
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                tie_guesser = candidates[preferences[i][j]].votes;
                j = candidate_count;
                i = voter_count;
                break;
            }
        }
    }


        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].eliminated == false && candidates[i].votes == tie_guesser)
            {
              tie ++;
            }
        }


    if (tie == tied)
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
return;
}
