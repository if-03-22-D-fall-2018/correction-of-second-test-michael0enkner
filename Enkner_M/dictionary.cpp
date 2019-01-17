/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			dictionary.cpp
 * Author:			P. Bauer
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Implementation of dictionary.h.
 * ----------------------------------------------------------
 */
#include "dictionary.h"
typedef struct NodeImplementation* Node;

struct NodeImplementation{
  const char* word;
  Node next;
};

struct DictionaryImplementation{
  int length;
  Node head;
  bool IsInterating;
};

Dictionary new_dictionary ()
{
  Dictionary dictionary = (Dictionary) malloc(sizeof(struct DictionaryImplementation));
  dictionary->length = 0;
  dictionary->head = 0;
  dictionary->IsInterating = false;
  return dictionary;
}

void 	delete_dictionary (Dictionary dictionary)
{
  Node current = dictionary->head;
  Node should_delete;
  while (current != 0)
  {
    should_delete = current;
    current = current->next;
    sfree(should_delete);
  }
  sfree(dictionary);
}

void 	add (Dictionary dict, const char *word)// added one row
{
  Node newword = (Node) malloc(sizeof(struct NodeImplementation));
  newword->next = 0;
  newword->word = word;
  Node current = dict->head;

  if (is_in_dict(dict,word))return ;
  if (dict->head == 0)
  {
    dict->head = newword;
  }
  else
  {
    while (current->next != 0)
    {
      current = current->next;
    }
    current->next = newword;
  }
  dict->length++;
}

int 	get_size (Dictionary dict)//new Implementation
{
  return dict->length;
}

bool 	is_in_dict (Dictionary dict, const char *word)
{
  Node current = dict->head;
  if (dict->head == 0)
  {
    return false;
  }
  while (current != 0)
  {
    if (strcasecmp(current->word,word) == 0)
    {
      return true;
    }
    current = current->next;
  }
  return false;
}

void 	start_iterating (Dictionary dict)
{
  dict->IsInterating = true;
}

bool 	has_next (Dictionary dict)
{
  if (dict->head != 0 && dict->IsInterating == true)
  {
    return true;
  }
  return false;
}

const char * 	get_next_entry (Dictionary dict)
{
  if (has_next(dict) == true && dict->IsInterating == true)
  {
    const char* word = dict->head->word;
    dict->head = dict->head->next;
    return word;
  }
  return 0; // Added return 0
}

void 	insert_sorted (Dictionary dict, const char *word)//New funktion
{
  Node current = dict->head;
  Node node_to_add = (Node) malloc(sizeof(struct NodeImplementation));
  node_to_add->word = word;
  node_to_add->next = 0;
  if(dict->head == 0)
  {
    add(dict, word);
  }
  else
  {
    if(is_in_dict(dict, word))
    {
      return;
    }

    if(strcasecmp(dict->head->word, word) > 0)
    {
      node_to_add->next = dict->head;
      dict->head = node_to_add;
      dict->length++;
    }
    else
    {
      while(current->next != 0 && strcasecmp(current->next->word, word) < 0)
      {
        current = current->next;
      }
      if(current->next == 0)
      {
        add(dict, word);
      }
      if(strcasecmp(current->next->word, word) > 0)
      {
        node_to_add->next = current->next;
        current->next = node_to_add;
        dict->length++;
      }
    }
  }
}
