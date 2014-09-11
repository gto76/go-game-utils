// Arguments:	1. string move ('ca' for first row, third columd),
//				2. int board size ('9' for size of 9x9), 
//				3. int transformations ('0' for no transformations).

// Transformations int with value 27 gets decoded in this way:
//
// freeze|trans.
// flags |flags
// +-----+-----+ ----------
// |0|1|1|0|1|1| flag value
// +-----+-----+ ----------
// |3|2|1|3|2|1| trans. no.
// +-----+-----+ ----------
// |6|5|4|3|2|1| bit number
// +-----+-----+ ----------

// Returns transformations (rotations, mirroring) that are neccesary for passed move to be in normalized form

// This program tries to find the transformations necessary for the game to be in normal state. Definition of normal state is that as many consecutive moves as posible from the begining of a game satisfy the following three conditions:
//	1. x >= 0
// 	2. y >= 0
//  3. x >= y
// 
// So for instance if first move doesent satisfy second condition then the y = -y transformation should be aplied to all moves, so the returned value has flags no. 2 and 5 set to 1. 

// Concrete example would be move "gc", board size 9 and transformations preset to 0. // First move gets transformed from "column-letter""row-letter" notation to (x-coordinate, y-coordinate) notation with (0,0) point at the center of the board. So with board size of 9, "gc" gets transformed into [2,2].
// Secondly program finds out which transformations have already been freezed. This is done by looking at the fourth, fifth and sixt bit of a passed int. Values of this bits coresspond to first, second, third transformation being frozen, thats already been decided by erlier invocations of this program that this transformations have to be applied to all the moves for this game to be in normal state. What is being asked of this invocation is which of the remaining (unfrozen) transformations should or should not be aplied.
// So in concrete example none have been frozen since 0 means tha last 6 bits are 000000. That means that we check [2,2] for the first condition (x >= 0), which it passes, but...


