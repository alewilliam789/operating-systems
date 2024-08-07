/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Basic utilities */

int splice_string(char* str,char* substr, int start, int end){
  
  if (start > end) {
    fprintf(stderr,"You can't splice a string in reverse.");
    return 1;
  }
 
  int i = start;
  int j = 0;
  while (i < end) {
    substr[j] = tolower(str[i]);
    i++;
    j++;
  }

  substr[j+1] = '\0';
  
  return 0;
}

char *new_string(char *str) {
  char *new_str = (char *) malloc(strlen(str) + 1);
  if (new_str == NULL) {
    return NULL;
  }
  return strcpy(new_str, str);
}

int init_words(WordCount **wclist) {
  /* Initialize word count.
     Returns 0 if no errors are encountered
     in the body of this function; 1 otherwise.
  */
  WordCount* wc = malloc(sizeof(WordCount));

  if(wc == NULL) {
    return 1;
  }

  wc->word = NULL;
  wc->count = 0;
  wc->next = NULL;

  *wclist = wc;
  return 0;
}

int new_word(WordCount* curr_wr, char* word) {
  /* Return 0 if given a word
   * and it's successfully allocated.
   * A 1 if not.
  */

  if (curr_wr->word == NULL && curr_wr->next == NULL) {
    curr_wr->word = word;
    curr_wr->count = 1;
    return 0;
  }
  
  WordCount* wc = malloc(sizeof(WordCount));

  if (wc == NULL) {
    fprintf(stderr, "Unable to allocate space for this word");
    return 1;
  }

  wc->word = word;
  wc->count = 1;
  wc->next = NULL;

  curr_wr->next = wc;

  return 0;
}

ssize_t len_words(WordCount *wchead) {
  /* Return -1 if any errors are
     encountered in the body of
     this function.
  */
    size_t len = 0;

    WordCount* wc = wchead;

    while(wc->word != NULL && wc->next != NULL) {
      len++;
      wc = wc->next;
    }

    return len;
}

WordCount* find_word(WordCount *wchead, char *word) {
  /* Return count for word, if it exists */
  WordCount* wc = wchead;
  
  while (wc->word != NULL) {
    char* curr_wrd = wc->word;

    if (strcmp(word, curr_wrd) == 0) {
      return wc;
    }
    
    if (wc->next != NULL) {
      wc = wc->next;
    }
    else {
      break;
    }
  }

  return wc;
}

int add_word(WordCount **wclist, char *word) {
  /* If word is present in word_counts list, increment the count.
     Otherwise insert with count 1.
     Returns 0 if no errors are encountered in the body of this function; 1 otherwise.
  */
 WordCount* curr_wc = find_word(*wclist, word);

 if (curr_wc->next != NULL && curr_wc->word != NULL) {
    if (strcmp(curr_wc->word, word) == 0) {
      curr_wc->count++; 
    }
 }
 else {
    if(new_word(curr_wc, word) != 0) {
      return 1;
    }
 }
  
 return 0;
}

void fprint_words(WordCount *wchead, FILE *ofile) {
  /* print word counts to a file */
  WordCount *wc;
  for (wc = wchead; wc; wc = wc->next) {
    if(wc->count > 0) {
      fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
    }
  }
}
