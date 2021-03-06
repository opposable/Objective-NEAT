/*
 * ObjectiveNEAT 0.1.0
 * Author: Ben Trewhella
 *
 * Copyright (c) 2011 OpposableIntelligence.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#import <Foundation/Foundation.h>
@class ONGenoNode;
@class ONGenoLink;

/**
 * The Innovation Database acts as a central repository for all innovations.
 *  
 * It consists of a private array of innovations, which can be checked for existing 
 * nodes or links using the possible... methods, and to which a node or link can be added
 * using the insert... methods.  Note the insert metheds do not check to see if an
 * innovation already exists so the calling function needs to first check for an 
 * existing item before inserting anything.
 *
 * There is only ever one innovations database and it should be accessed using the
 * sharedDB class method.
 *
 * In future this could be moved to a web service to allow multiple devices to share a population.
 */

@interface ONInnovationDB : NSObject {
    NSMutableArray * linkInnovations;
    NSMutableArray * nodeRecord;
}

/**
 * Consult the Innovation DB to find the specified node
 */
-(ONGenoNode *) getNodeWithID: (int) nodeID;

/** 
 * Checks to see if a node already exists between the fNode and tNode
 * which would indicate another genome has found this innovation.
 * In that case a COPY of the existing node is returned.   If no node is found 
 * the method returns nil, so that a new node can be created.
 */
-(ONGenoNode *) possibleNodeExistsFromNode: (int) fNode toNode: (int) tNode;

/** 
 * Inserts a new node innovation into the database.
 * This could potentially be combined with the possibleNodeExists... check
 * but this would require the whole shebang to be past through which seems unneccesary.
 */
-(void) insertNewNode:(ONGenoNode *) newNode fromNode:(int) fNode toNode: (int) tNode;

/** 
 * Checks to see if a link already exists between the fNode and tNode
 * which would indicate another genome has found this innovation.
 * In that case a COPY of the existing link is returned.   If no link is found 
 * the method returns nil, so that a new link can be created.
 */
-(void) insertNewLink:(ONGenoLink *) newLink fromNode:(int) fNode toNode: (int) tNode;

/** 
 * Inserts a new link innovation into the database.
 * This could potentially be combined with the possibleLinkExists... check
 * but this would require the whole shebang to be past through which seems unneccesary.
 */
-(ONGenoLink *) possibleLinkExistsFromNode: (int) fNode toNode: (int) tNode;

/**
 * There should only ever be one Innovation Database so it is implemented as 
 * a singleton, the sharedDB method will provide the single instance.
 * Note this has not been strongly enforced, it is possible to create other 
 * Innovation Databases, just in case this proves useful.
 */
+(ONInnovationDB *) sharedDB;

/** Provides the next Genome ID, to be used when a genuinely new GenoNode is created */
+(int) getNextGenoNodeID;

/** Provides the next Innovation ID, used by an Innovations init method */
+(int) getNextInnovationID;


@end
