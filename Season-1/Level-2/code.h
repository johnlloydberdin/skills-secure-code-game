// Welcome to Secure Code Game Season-1/Level-2!

// Follow the instructions below to get started:

// 1. Perform code review. Can you spot the bug? 
// 2. Run tests.c to test the functionality
// 3. Run hack.c and if passing then CONGRATS!
// 4. Compare your solution with solution.c

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constants
#define MAX_USERNAME_LEN 39       // Maximum length for usernames
#define SETTINGS_COUNT 10         // Number of settings per user
#define MAX_USERS 100             // Maximum number of users allowed
#define INVALID_USER_ID -1        // Constant for invalid user ID

// Global Variables
int userid_next = 0;              // Internal counter of user accounts

// Structure Definitions
// Represents a user account (private and implementation-specific)
typedef struct {
    bool isAdmin;                     // Flag for admin status
    long userid;                      // Unique user ID
    char username[MAX_USERNAME_LEN + 1];  // User's username
    long setting[SETTINGS_COUNT];     // Array of settings for the user
} user_account;

// Simulates an internal store of active user accounts
user_account *accounts[MAX_USERS] = { NULL };  // Initialize account store with NULL pointers

// Function Definitions

/**
 * Creates a new user account and returns its unique identifier.
 * @param isAdmin Indicates if the user is an admin.
 * @param username The username for the new account.
 * @return The unique user ID, or INVALID_USER_ID if an error occurs.
 */
int create_user_account(bool isAdmin, const char *username) {
    if (userid_next >= MAX_USERS) {
        fprintf(stderr, "The maximum number of users have been exceeded\n");
        return INVALID_USER_ID;
    }

    if (strlen(username) > MAX_USERNAME_LEN) {
        fprintf(stderr, "The username is too long\n");
        return INVALID_USER_ID;
    }

    user_account *ua = malloc(sizeof(user_account));
    if (ua == NULL) {
        fprintf(stderr, "Malloc failed to allocate memory\n");
        return INVALID_USER_ID;
    }

    ua->isAdmin = isAdmin;
    ua->userid = userid_next;
    strcpy(ua->username, username);
    memset(ua->setting, 0, sizeof(ua->setting));
    accounts[userid_next] = ua;  // Assign the user account before incrementing
    return userid_next++;
}

/**
 * Updates the matching setting for the specified user and returns the status.
 * @param user_id The ID of the user to update.
 * @param index The index of the setting to update.
 * @param value The new value for the setting.
 * @return True if the update was successful, false otherwise.
 */
bool update_setting(int user_id, const char *index, const char *value) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL) {
        return false;
    }

    char *endptr;
    long i = strtol(index, &endptr, 10);
    if (*endptr || i < 0 || i >= SETTINGS_COUNT) {  // Ensure index is within valid range
        return false;
    }

    long v = strtol(value, &endptr, 10);
    if (*endptr) {  // Ensure value is a valid number
        return false;
    }

    accounts[user_id]->setting[i] = v;  // Update the setting
    return true;
}

/**
 * Checks whether the specified user is an admin.
 * @param user_id The ID of the user to check.
 * @return True if the user is an admin, false otherwise.
 */
bool is_admin(int user_id) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL) {
        fprintf(stderr, "Invalid user ID\n");
        return false;
    }
    return accounts[user_id]->isAdmin;
}

/**
 * Retrieves the username of the specified user.
 * @param user_id The ID of the user.
 * @return The username, or NULL if the user ID is invalid.
 */
const char* username(int user_id) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL) {
        fprintf(stderr, "Invalid user ID\n");
        return NULL;
    }
    return accounts[user_id]->username;
}
