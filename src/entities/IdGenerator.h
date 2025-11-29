/***
 * IdGenerator: 
 *  -> Brief: Simple incrementing id generator used by repositories (header-only)
***/

#ifndef CS_3140_PROJECT_IDGENERATOR_H
#define CS_3140_PROJECT_IDGENERATOR_H


class IdGenerator {
public:
    // Return a monotonically increasing id (starts at 1)
    static int generateId() {
        static int nextId = 1;
        return nextId++;
    }
};


#endif //CS_3140_PROJECT_IDGENERATOR_H