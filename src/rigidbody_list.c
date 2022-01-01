#include "speed.h"

Rigidbody_List *new_rigidbody_list() {
  Rigidbody_List *rigidbody_list =
      (Rigidbody_List *)malloc(sizeof(Rigidbody_List));

  rigidbody_list->rigidbody = NULL;
  rigidbody_list->prev = NULL;
  rigidbody_list->next = NULL;
  return rigidbody_list;
}

// Add a new member to the list
// Binds it correctly
// Then returns said created members pointer
Rigidbody_List *add_member_to_end_of_list(Rigidbody_List *start,
                                          Rectangle *target_rectangle) {
  Rigidbody_List *swp = start;

  while (swp->next != NULL)
    swp = swp->next;
  swp->next = new_rigidbody_list();
  swp->next->prev = swp;
  swp->next->rigidbody = new_rigidbody(target_rectangle);
  return swp->next;
}

// Adds a new member to the start of the list
// Returns the new start
Rigidbody_List *add_member_to_start_of_list(Rigidbody_List *start,
                                            Rectangle *target_rectangle) {
  start->prev = new_rigidbody_list();
  start->prev->next = start;
  start->prev->rigidbody = new_rigidbody(target_rectangle);
  return start->prev;
}

// Frees the memory associated with the member, next and prevs still points to
// this now freed block !
void destroy_rigidbody_list_member(Rigidbody_List *target_member) {
  destroy_rigidbody(target_member->rigidbody);
  free(target_member);
}

void remove_member_from_list(Rigidbody_List *target_member) {
  if (target_member->next != NULL) {
    target_member->next = target_member->prev;
  }
  if (target_member->prev != NULL) {
    target_member->prev = target_member->next;
  }
  destroy_rigidbody_list_member(target_member);
}

void destroy_rigidbody_list(Rigidbody_List *start) {
  Rigidbody_List *swp = start;
  Rigidbody_List *next = NULL;

  while (swp != NULL) {
    next = swp->next;
    destroy_rigidbody_list_member(swp);
    swp = next;
  }
}