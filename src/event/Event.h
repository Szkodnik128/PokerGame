//
// Created by kuba on 18.03.18.
//

#ifndef POKERGAME_EVENT_H
#define POKERGAME_EVENT_H

class Event {

protected:
    const void *const clientHandler;

public:
    explicit Event(const void *const clientHandler);
    virtual ~Event() = default;
    const void *const getClientHandler() const;
};


#endif //POKERGAME_EVENT_H
