#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "rowing.h"

#define Boat std::tuple<std::string, int, int, int, bool> // Name, max_crew, kms, n_excs, in_use
#define Boats std::vector<Boat>

#define BOAT_NAME_POS 0
#define BOAT_MAX_CREW_POS 1
#define BOAT_KMS_POS 2
#define BOAT_N_EXCS_POS 3
#define BOAT_IN_USE_POS 4

#define Member std::tuple<std::string, int, int, bool> // Name, km, n_excs, in_exc
#define Members std::vector<Member>

#define MEMBER_NAME_POS 0
#define MEMBER_KM_POS 1
#define MEMBER_N_EXCS_POS 2
#define MEMBER_IN_EXC 3

#define Excursions std::vector<excursion>

#define NO_BOAT nullptr

struct club
{
private:
    Boats boats;
    Members members;

public:
    // Constructors
    club() {}
    club(const club &c) : boats(c.boats) {} // copy-constructor

    // Destructor
    ~club() {}

    // Methods

    // Return iterator to boat by name
    Boats::iterator find_boat(std::string boat_name)
    {
        // return boat by reference
        for (auto it = boats.begin(); it != boats.end(); ++it)
        {
            if (std::get<BOAT_NAME_POS>(*it) == boat_name)
                return it;
        }

        return boats.end();
    }

    Boat &get_boat_reference(std::string boat_name)
    {
        return *(find_boat(boat_name));
    }

    Member &get_member_reference(std::string member_name)
    {
        return *(find_member(member_name));
    }

    // Return iterator to member by name
    Members::iterator find_member(std::string member_name)
    {
        // return boat by reference
        for (auto it = members.begin(); it != members.end(); ++it)
        {
            if (std::get<MEMBER_NAME_POS>(*it) == member_name)
                return it;
        }

        return members.end();
    }

    int add_boat(std::string boat_name, int max_crew)
    {
        // look for boats with same name
        if (find_boat(boat_name) != boats.end())
            return 0;

        // no duplicate found, can add boat
        try
        {
            boats.push_back(std::make_tuple(boat_name, max_crew, 0, 0, false));
            return 1;
        }
        catch (const std::exception &e)
        {
            // meory error
            return 0;
        }
    }

    int add_person(std::string member_name)
    {
        // look for duplicate
        if (find_member(member_name) != members.end())
            return 0;

        // no duplicates
        try
        {
            members.push_back(std::make_tuple(member_name, 0, 0, false));
            return 1;
        }
        catch (const std::exception &e)
        {
            // memory error
            return 0;
        }
    }

    bool is_boat_present(std::string boat_name)
    {
        return find_boat(boat_name) != boats.end();
    }

    bool is_member_present(std::string member_name)
    {
        return find_member(member_name) != members.end();
    }

    int get_boat_kms(std::string boat_name)
    {
        return std::get<BOAT_KMS_POS>(get_boat_reference(boat_name));
    }

    int get_boat_excs(std::string boat_name)
    {
        return std::get<BOAT_N_EXCS_POS>(get_boat_reference(boat_name));
    }

    bool is_boat_in_use(std::string boat_name)
    {
        return std::get<BOAT_IN_USE_POS>(get_boat_reference(boat_name));
    }
};

struct excursion
{
private:
    Boat *used_boat = nullptr;
    club *owner_club = nullptr;
    std::vector<Member *> members;

public:
    // Constructors
    excursion(){};
    excursion(club *owner_club) : owner_club(owner_club){};
    excursion(const excursion &e) : used_boat(e.used_boat), owner_club(e.owner_club), members(e.members){}; // copy-constructor

    // Destructor
    ~excursion()
    {
        // set all members to not in exc
        for (Member *member : members)
        {
            std::get<MEMBER_IN_EXC>(*member) = false;
        }

        // set the boat to available
        if (is_boat_valid())
        {
            Boat &boat = *used_boat;
            std::get<BOAT_IN_USE_POS>(boat) = false;
        }
    }

    bool is_boat_valid()
    {
        return used_boat != nullptr;
    }

    // Methods
    Boat &get_used_boat()
    {
        return *used_boat;
    }

    void set_used_boat(Boat &new_used_boat)
    {
        std::get<BOAT_IN_USE_POS>(new_used_boat) = true;
        used_boat = &new_used_boat;
    }

    club &get_club()
    {
        return *owner_club;
    }

    void add_member(Member &member)
    {
        std::get<MEMBER_IN_EXC>(member) = true;
        members.push_back(&member);
    }

    int get_crew_size()
    {
        return members.size();
    }

    void close_excursion(int kms)
    {
        // Increase the n_excs of the boat
        Boat &boat = *used_boat;
        std::get<BOAT_N_EXCS_POS>(boat)++;

        // Add the kms to the boat
        std::get<BOAT_KMS_POS>(boat) += kms;

        // Increase the n_excs to all members
        // Increase the kms to all members
        for (Member *temp_m_add : members)
        {
            // Member &temp_m = *temp_m_add;
            std::get<MEMBER_N_EXCS_POS>(*temp_m_add)++;
            std::get<MEMBER_KM_POS>(*temp_m_add) += kms;
        }
    }
};

struct club *create_club()
{
    try
    {
        club *new_club = new club();
        return new_club;
    }
    catch (const std::exception &e)
    {
        // error
        return nullptr;
    }
}
void destroy_club(struct club *c)
{
    delete c;
}

int add_boat(struct club *c, const char *name, unsigned int max_crew)
{
    if (max_crew < 1)
        return 0;

    return c->add_boat(name, max_crew);
}
int add_person(struct club *c, const char *member_name)
{
    return c->add_person(member_name);
}

struct excursion *create_excursion(struct club *c)
{
    try
    {
        return new excursion(c);
    }
    catch (const std::exception &e)
    {
        // error
        return nullptr;
    }
}

int use_boat(struct excursion *e, const char *boat_name)
{
    club &exc_club = e->get_club();

    // check if boat exists
    if (exc_club.is_boat_present(boat_name) == false)
        return 0;

    // Get the boat
    Boat &boat = exc_club.get_boat_reference(boat_name);

    // check if boat is in use
    if (std::get<BOAT_IN_USE_POS>(boat))
        return 0;

    // Boat is valid
    e->set_used_boat(boat);

    return 1;
}
int add_crew(struct excursion *e, const char *member_name)
{
    club &exc_club = e->get_club();

    // no boat used
    if (e->is_boat_valid() == false)
        return 0;

    Boat &used_boat = e->get_used_boat();

    // max-size reached
    if (std::get<BOAT_MAX_CREW_POS>(used_boat) == e->get_crew_size())
        return 0;

    // check if member in club of excursion
    if (!(exc_club.is_member_present(member_name)))
        return 0;

    // check if member is already in an excursion
    Member &member = exc_club.get_member_reference(member_name);
    if (std::get<MEMBER_IN_EXC>(member))
        return 0;

    // ALL GOOD! ADD THE MEMBER TO THE EXCURSION
    e->add_member(member);
    return 1;
}

int close_excursion(struct excursion *e, unsigned int kms)
{
    // no boat used
    if (e->is_boat_valid() == false)
        return 0;

    Boat &used_boat = e->get_used_boat();
    // not enough crew
    if (std::get<BOAT_MAX_CREW_POS>(used_boat) < 1)
        return 0;

    // ALL GOOD!
    e->close_excursion(kms);
    delete e;
    return 1;
}
void cancel_excursion(struct excursion *e)
{
    delete e;
}

int get_crew_excursions(struct club *c, const char *member_name)
{
    if (c->is_member_present(member_name) == false)
        return -1;

    Member &member = c->get_member_reference(member_name);

    return std::get<MEMBER_N_EXCS_POS>(member);
}
int get_crew_kilometers(struct club *c, const char *member_name)
{
    if (c->is_member_present(member_name) == false)
        return -1;

    Member &member = c->get_member_reference(member_name);

    return std::get<MEMBER_KM_POS>(member);
}

int boat_available(struct club *c, const char *boat_name)
{
    if (!(c->is_boat_present(boat_name)))
        return -1;

    return c->is_boat_in_use(boat_name) ? 0 : 1;
}
int get_boat_excursions(struct club *c, const char *boat_name)
{
    if (!(c->is_boat_present(boat_name)))
        return -1;
    else
        return c->get_boat_excs(boat_name);
}
int get_boat_kilometers(struct club *c, const char *boat_name)
{
    if (!(c->is_boat_present(boat_name)))
        return -1;
    else
        return c->get_boat_kms(boat_name);
}
