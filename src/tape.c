//  tape.c
//  aoneill - 06/25/16

#include "tape.h"

cell_t* _create_cell(int id) {
  // Create a cell on the stack and populate it (with position)
  cell_t* cell = malloc(sizeof(cell_t));
  cell -> id = id;
  cell -> content = 0;
  cell -> neg = NULL;
  cell -> pos = NULL;

  return cell;
}

void _tape_extend(tape_t* tape, int dir, int num) {
  // Start at the origin
  cell_t* origin = tape -> origin;
  while(num > 0) {
    if(dir == _DIR_NEG) {
      // Create a more negative cell if it doesn't exist
      if(origin -> neg == NULL) {
        cell_t* cell = _create_cell(origin -> id - 1);

        // Link properly
        origin -> neg = cell;
        cell -> pos = origin;
        num--;
      }
      
      // Move on
      origin = origin -> neg;
    }
    else if(dir == _DIR_POS) {
      // Create a more positive cell if it doesn't exist
      if(origin -> pos == NULL) {
        cell_t* cell = _create_cell(origin -> id + 1);

        // Link properly
        origin -> pos = cell;
        cell -> neg = origin;
        num--;
      }
      
      // Move on
      origin = origin -> pos;
    }
  }
}

void tape_init(tape_t* tape) {
  // Create a cell at the origin
  tape -> origin = _create_cell(0);
  tape -> current = tape -> origin;
  tape -> pos = 0;

  // Extend the tape to the right size in both directions
  _tape_extend(tape, _DIR_NEG, INIT_TAPE_LEN_NEG);
  _tape_extend(tape, _DIR_POS, INIT_TAPE_LEN_POS - 1);
}

void tape_goto(tape_t* tape, int pos) {
  // Go positively if we are below
  while(tape -> pos < pos) {
    // Create if we need to
    if(tape -> current -> pos == NULL) {
      cell_t* cell = _create_cell(tape -> current -> id + 1);
      tape -> current -> pos = cell;
      cell -> neg = tape -> current;
    }
      
    // Move
    tape -> current = tape -> current -> pos;
    tape -> pos++;
  }

  // Go negatively if we are above
  while(tape -> pos > pos) {
    // Create if we need it
    if(tape -> current -> neg == NULL) {
      cell_t* cell = _create_cell(tape -> current -> id - 1);
      tape -> current -> neg = cell;
      cell -> pos = tape -> current;
    }
      
    // Move
    tape -> current = tape -> current -> neg;
    tape -> pos--;
  }
}

int tape_get(tape_t* tape) {
  // Get the number at the position
  return tape -> current -> content;
}

void tape_set(tape_t* tape, int val) {
  // Set the value
  tape -> current -> content = val;
}

void tape_inc(tape_t* tape) {
  // Increment
  tape -> current -> content++;
}

void tape_dec(tape_t* tape) {
  // Decrement
  tape -> current -> content--;
}

void _cell_free(cell_t* cell) {
  // Free all negative cells
  while(cell != NULL && cell -> neg != NULL) {
    cell_t* item = cell -> neg;
    cell -> neg = cell -> neg -> neg;
    free(item);
  }
  
  // Free all positive cells
  while(cell != NULL && cell -> pos != NULL) {
    cell_t* item = cell -> pos;
    cell -> pos = cell -> pos -> pos;
    free(item);
  }

  // Free the root
  free(cell);
}

void tape_free(tape_t* tape) {
  // Viva la revolucion!
  _cell_free(tape -> origin);
}
  
void tape_print(tape_t* tape) {
  // Pick the most negative
  cell_t* runner = (tape -> origin -> id) > (tape -> current -> id) ?
    tape -> origin : tape -> current;
  cell_t* follower = runner -> pos;
  
  // Get the last non-null cell
  while(runner != NULL) {
    follower = runner;
    runner = runner -> neg;
  }

  // Print as if it were a list
  printf("[");
  while(follower != NULL) {
    printf("%2d", follower -> content);
    printf("%s", follower -> pos == NULL ? "]\n" : ", ");
    follower = follower -> pos;
  }
}
  
int tape_verify(tape_t* tape) {
  // Pick the most negative
  cell_t* runner = (tape -> origin -> id) > (tape -> current -> id) ?
    tape -> origin : tape -> current;
  cell_t* follower = runner -> pos;
  
  // Get the most negative non-null cell
  while(runner != NULL) {
    follower = runner;
    runner = runner -> neg;
  }

  int found_current = 0;
  while(follower != NULL) {
    // Verify the relatinships between cells
    cell_t* old = follower;

    found_current = (follower == tape -> current) || found_current;
    follower = follower -> pos;
    if(follower == NULL)
      break;

    if(old -> id != follower -> id - 1) {
      return 0;
    }

    if(follower -> neg != old) {
      return 0;
    }
  }

  // Make sure the overall strucure is good
  return found_current && tape -> current -> id == tape -> pos;
}
