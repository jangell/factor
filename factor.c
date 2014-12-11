// Jason Angell
// [needs better hobbies]

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define TOTALPERCENT 50

struct node{
  int val;
  struct node * next;
};

int parse_num();
int next_prime();
int check_if_prime();

int main(int argc, char * argv[]){
  if(argc != 2){
    printf("c'mon dude, you gotta input an argument!\n");
    return 1;
  }
  int mainnum = parse_num(argv[1]);
  if(mainnum == INT_MAX){
    printf("%s? what in the hell is %s? input a number, dawg\n", argv[1], argv[1]);
    return 1;
  }
  else if(mainnum == INT_MAX - 1){
    printf("actually, that was all i've got. CONNECTION TERMINATED\n");
    return 1;
  }
  int workingnum = mainnum;
  struct node * primes = malloc(sizeof(struct node));
  primes->val = -1; // dummy last node
  primes->next = NULL;
  struct node * factors = malloc(sizeof(struct node));
  factors->val = -1; // dummy last node
  factors->next = NULL;

  // let's factor this biznitch

  if(workingnum == 0){
    printf("zero is a silly number\n");
    return 0;
  }
  else if(workingnum == 1){
    printf("ERROR ABORT SYSTEM OVERBOOT DRIVE CONTROL ERROR SYSTEM UNDERJARGON SNEEZEBOT 5000 TROPICAL DICTATORSHIP INTERGALACTIC PLANETARY\n");
    sleep(1);
    printf("why? why one? that's stupid. it's one. one is one. it's always goddamn one.\n");
    return 0;
  }

  if(workingnum < 0){
    printf("thought you'd get clever, eh? negative number and a11##@-1SYSTEMOVERLOADERROR\n");
    int i = 0;
    while(i < 5){
      sleep(1);
      printf(".\n");
      i++;
    }
    printf("nope, just kidding. i can handle negatives, no problemo. it's cool. don't mention it.\n");
    struct node * add = malloc(sizeof(struct node));
    add->val = -1;
    add->next = factors;
    factors = add;
    workingnum = workingnum * -1;
  }
    
  
  int counting = 2;
  while(workingnum > 1){
  	while(workingnum % counting == 0){
      workingnum = workingnum / counting;
      struct node * addfactor = malloc(sizeof(struct node));
      addfactor->val = counting;
      addfactor->next = factors;
      factors = addfactor;
    }
    counting = next_prime(counting, primes);
    //printf("%i\n", counting); // uncomment if you want verbose (it's helllll)
    // add it to primes
    struct node * addprime = malloc(sizeof(struct node));
    addprime->val = counting;
    addprime->next = primes;
    primes = addprime;
    // check if it's a factor
  }

  // print factors here
  // todo: reverse order, improve formatting

  printf("The factors of %i are", mainnum);
  while(factors->next != NULL){
    printf(" %i", factors->val);
    factors = factors->next;
  }
  printf("\n");

  return 0;
  
}


// parses an int out of a string
int parse_num(char numstring[]){
  int neg = 0;
  int to_ret = 0;
  int i = 0;
  if(numstring[0] == '-'){
    i = 1;
    neg = -1;
  }
  /*
   * the following loop is tricky, and here's why: the second condition prevents
   * a number input that's bigger than the max int, but the way it does that is
   * a bit strange. so what it's really checking is that ten times the current
   * total (to_ret) is less than the max integer value, but in the next cycle it's
   * also going to add between 0 and 9, so we have to make sure there's room for that
   * too. really, we're still preventing about ten inputs, but it's the ten up to
   * max_int, and i'm not going to lose any sleep over lowering my max by 0.0000001%.
   * Plus, this means those numbers can be error values.
   */
  while(numstring[i] != '\0'){
    if(! isdigit(numstring[i])){
      return INT_MAX;
    }
    to_ret = to_ret * 10;
    to_ret += (numstring[i] - '0');
    i++;
    if((to_ret + 1) > INT_MAX / 10){
      printf("There's gonna be another snarky error message below this, but this is the REAL snarky error message:\n");
      sleep(1);
      printf("Yo mama so fat, she has an intuitive sense of the size of the number you just input.\n");
      sleep(3);
      printf("I'm gonna stop for a second to let that sink in.\n");
      sleep(5);
      printf("now input something reasonable, brochevski\n");
      return INT_MAX - 1;
    }
  }
  if(neg){
    to_ret = to_ret * -1;
  }
  return to_ret;
}

// gets the next prime, given any positive integer
int next_prime(int cur_int, struct node * primes){
  cur_int++;
  while(check_if_prime(cur_int, primes) == 0){
    cur_int++;
  }
  return cur_int;
}

// checks if a number is prime, via the working list of primes (prime returns 1)
int check_if_prime(int checkme, struct node * primes){
  while(primes->next != NULL && checkme / primes->val > 1){
    // second condition in above line: if less than twice largest prime, # automatically prime
    if((checkme % primes->val) == 0){
      return 0;
    }
    primes = primes->next;
  }
  // hey, it's prime!
  return 1;
  
}
