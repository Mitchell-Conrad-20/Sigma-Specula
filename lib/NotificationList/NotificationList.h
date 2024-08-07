#ifndef NOTIFICATIONLIST_H
#define NOTIFICATIONLIST_H

#include <vector>
#include <string>
#include <esp32notifications.h>

class NotificationList {
private:
    std::vector<Notification> notifications;
    std::vector<Notification> textNotifications;

public:
    NotificationList();

    std::vector<Notification> getNotifications() const;
    std::vector<Notification> getTextNotifications() const;
    void reset();
    void addNotification(const Notification* notification);
    int removeNotification(const Notification* notification);
};

#endif // NOTIFICATIONLIST_H