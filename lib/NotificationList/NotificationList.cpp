#include "NotificationList.h"

/****** Constructor ******/
NotificationList::NotificationList() {
    // Do nothing, notifications vectors are automatically initialized
}

/****** Public Methods ******/

// Get the current notifications list
std::vector<Notification> NotificationList::getNotifications() const {
    return notifications;
}

// Get the current text notifications list
std::vector<Notification> NotificationList::getTextNotifications() const {
    return textNotifications;
}

// Reset the notifications list
void NotificationList::reset(){
    notifications.clear();
    textNotifications.clear();
}

// Add Notification to the List
void NotificationList::addNotification(const Notification* notification) {
    // Add a copy of the notification to the vector
    notifications.push_back(*notification);

    // If it is text message, also add to text notifications vector
    if (notification->type == "com.apple.MobileSMS"){
        textNotifications.push_back(*notification);
    }
}

// Remove Notification From the List
// Returns 0 if removed successfully
int NotificationList::removeNotification(const Notification* notification) {
    // Check if it is a text notification
    if (notification->type == "com.apple.MobileSMS"){
        // Iterate through the vector and remove the matching notification
        for (auto it = textNotifications.begin(); it != textNotifications.end(); ++it) {
            if (it->title == notification->title && it->message == notification->message && it->type == notification->type) {
                // Found the message, remove it
                textNotifications.erase(it);

                // Removed successfully
                break;
            }
        }
    }

    // Remove from the regular list of notifications
    // Iterate through the vector and remove the matching notification
    for (auto it = notifications.begin(); it != notifications.end(); ++it) {
        if (it->title == notification->title &&
            it->message == notification->message &&
            it->type == notification->type) {
            notifications.erase(it);
            return 0; // Removed successfully
        }
    }
    return 1; // Not found
}