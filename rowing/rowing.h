#ifndef ROWING_H_INCLUDED
#define ROWING_H_INCLUDED

struct club;
struct excursion;

#ifdef __cplusplus
extern "C" {
#endif

struct club * create_club ();
void destroy_club (struct club *);

int add_boat (struct club *, const char *, unsigned int);
int add_person (struct club *, const char *);

struct excursion * create_excursion (struct club *);
int use_boat (struct excursion *, const char *);
int add_crew (struct excursion *, const char *);

int close_excursion (struct excursion *, unsigned int);
void cancel_excursion (struct excursion *);

int get_crew_excursions (struct club *, const char *);
int get_crew_kilometers (struct club *, const char *);

int boat_available (struct club *, const char *);
int get_boat_excursions (struct club *, const char *);
int get_boat_kilometers (struct club *, const char *);

#ifdef __cplusplus
}
#endif

#endif
