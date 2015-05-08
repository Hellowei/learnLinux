/*****************************************************************************************
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2011.04.15
文件名:				
作者:				和心重典
功能说明:			
其它说明:			无
所属文件关系:		本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/

#ifndef __CHAIN_h
#define __CHAIN_h

#include "address.h"


#define  CHAIN_ENTER_CRITICAL()   OS_ENTER_CRITICAL()
#define  CHAIN_EXIT_CRITICAL()	OS_EXIT_CRITICAL()


/*
 *  This is used to manage each element (node) which is placed
 *  on a chain.
 *
 *  NOTE:  Typically, a more complicated structure will use the
 *		 chain package.  The more complicated structure will
 *		 include a chain node as the first element in its
 *		 control structure.  It will then call the chain package
 *		 with a pointer to that node element.  The node pointer
 *		 and the higher level structure start at the same address
 *		 so the user can cast the pointers back and forth.
 */

struct Chain_Node_struct;

typedef struct Chain_Node_struct {
	struct Chain_Node_struct *next;
	struct Chain_Node_struct *previous;
} CHAIN_NODE, *PCHAIN_NODE;


/*
 *  This is used to manage a chain.  A chain consists of a doubly
 *  linked list of zero or more nodes.
 *
 *  NOTE:  This implementation does not require special checks for
 *		 manipulating the first and last elements on the chain.
 *		 To accomplish this the chain control structure is 
 *		 treated as two overlapping chain nodes.  The permanent
 *		 head of the chain overlays a node structure on the
 *		 first and permanent_null fields.  The permanent tail
 *		 of the chain overlays a node structure on the 
 *		 permanent_null and last elements of the structure.
 */

typedef struct {
	CHAIN_NODE *first;
	CHAIN_NODE *permanent_null;
	CHAIN_NODE *last;
} CHAIN_CONTROL, *PCHAIN_CONTROL;

/* 
 *  _Chain_Initialize
 *
 *  This routine initializes the_chain structure to manage the
 *  contiguous array of number_nodes nodes which starts at
 *  starting_address.  Each node is of node_size bytes.
 */
VOID _Chain_Initialize( 
						CHAIN_CONTROL *the_chain,
						VOID		  *starting_address,
						UINT32		 number_nodes,
						UINT32		 node_size
					  );


/* 
 *  _Chain_Initialize_empty
 *
 *  This routine initializes the specified chain to contain zero nodes.
 */
VOID _Chain_Initialize_empty(CHAIN_CONTROL *the_chain);


/* 
 *  _Chain_Extract_unprotected
 *
 *  This routine extracts the_node from the chain on which it resides.
 *  It does NOT disable interrupts to insure the atomicity of the
 *  extract operation.
 */
VOID _Chain_Extract_unprotected(CHAIN_NODE *the_node);


/* 
 *  _Chain_Extract
 *
 *  This routine extracts the_node from the chain on which it resides.
 *  It disables interrupts to insure the atomicity of the
 *  extract operation.
 */
VOID _Chain_Extract(CHAIN_NODE *the_node);


/* 
 *  _Chain_Get_unprotected
 *
 *  This function removes the first node from the_chain and returns
 *  a pointer to that node.  If the_chain is empty, then NULL is returned.
 *  It does NOT disable interrupts to insure the atomicity of the
 *  get operation.
 */
CHAIN_NODE *_Chain_Get_unprotected(CHAIN_CONTROL *the_chain);


/* 
 *  _Chain_Get
 *
 *  This function removes the first node from the_chain and returns
 *  a pointer to that node.  If the_chain is empty, then NULL is returned.
 *  It disables interrupts to insure the atomicity of the
 *  get operation.
 */
CHAIN_NODE *_Chain_Get(CHAIN_CONTROL *the_chain);


/* 
 *  _Chain_Get_first_unprotected
 *
 *  This function removes the first node from the_chain and returns
 *  a pointer to that node.  It does NOT disable interrupts to insure
 *  the atomicity of the get operation.
 */
CHAIN_NODE *_Chain_Get_first_unprotected(CHAIN_CONTROL *the_chain);


/* 
 *  _Chain_Insert_unprotected
 *
 *  This routine inserts the_node on a chain immediately following
 *  after_node.  It does NOT disable interrupts to insure the atomicity
 *  of the extract operation.
 */
VOID _Chain_Insert_unprotected(CHAIN_NODE *after_node, CHAIN_NODE *the_node);


/* 
 *  _Chain_Insert
 *
 *  This routine inserts the_node on a chain immediately following
 *  after_node.  It disables interrupts to insure the atomicity
 *  of the extract operation.
 */
VOID _Chain_Insert(CHAIN_NODE *after_node, CHAIN_NODE *the_node);


/* 
 *  _Chain_Append_unprotected
 *
 *  This routine appends the_node onto the end of the_chain.
 *  It does NOT disable interrupts to insure the atomicity of the
 *  append operation.
 */
VOID _Chain_Append_unprotected(CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node);


/* 
 *  _Chain_Append
 *
 *  This routine appends the_node onto the end of the_chain.
 *  It disables interrupts to insure the atomicity of the
 *  append operation.
 */
VOID _Chain_Append(CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node);


/* 
 *  _Chain_Prepend_unprotected
 *
 *  This routine prepends the_node onto the front of the_chain.
 *  It does NOT disable interrupts to insure the atomicity of the
 *  prepend operation.
 */
VOID _Chain_Prepend_unprotected(CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node);


/* 
 *  _Chain_Prepend
 *
 *  This routine prepends the_node onto the front of the_chain.
 *  It disables interrupts to insure the atomicity of the
 *  prepend operation.
 */
VOID _Chain_Prepend(CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node);


/*
 *  _Chain_Insert_chain
 *
 *  This routine inserts a chain after the specified node in another
 *  chain. It is assumed that the insert after node is not on the
 *  second chain.
 */
VOID _Chain_Insert_chain(CHAIN_NODE *insert_after,CHAIN_CONTROL *to_insert);


/* 
 *  _Chain_Head
 *
 *  This function returns a pointer to the first node on the chain.
 */
CHAIN_NODE *_Chain_Head(CHAIN_CONTROL *the_chain);


/* 
 *  _Chain_Tail
 *
 *  This function returns a pointer to the last node on the chain.
 */
CHAIN_NODE *_Chain_Tail(CHAIN_CONTROL *the_chain);


/* 
 *  _Chain_Is_head
 *
 *  This function returns TRUE if the_node is the head of the_chain and
 *  FALSE otherwise.
 */
BOOL _Chain_Is_head(CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node);


/* 
 *  _Chain_Is_tail
 *
 *  This function returns TRUE if the_node is the tail of the_chain and
 *  FALSE otherwise.
 */
BOOL _Chain_Is_tail(CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node);


/* 
 *  _Chain_Is_first
 *
 *  This function returns TRUE if the_node is the first node on a chain and
 *  FALSE otherwise.
 */
BOOL _Chain_Is_first(CHAIN_NODE *the_node);


/* 
 *  _Chain_Is_last
 *
 *  This function returns TRUE if the_node is the last node on a chain and
 *  FALSE otherwise.
 */
BOOL _Chain_Is_last(CHAIN_NODE *the_node);


/* 
 *  _Chain_Is_empty
 *
 *  This function returns TRUE if there a no nodes on the_chain and
 *  FALSE otherwise.
 */
BOOL _Chain_Is_empty(CHAIN_CONTROL *the_chain);


/* 
 *  _Chain_Has_only_one_node
 *
 *  This function returns TRUE if there is only one node on the_chain and
 *  FALSE otherwise.
 */
BOOL _Chain_Has_only_one_node(CHAIN_CONTROL *the_chain);


/* 
 *  _Chain_Is_null
 *
 *  This function returns TRUE if the_chain is NULL and FALSE otherwise.
 */
BOOL _Chain_Is_null(CHAIN_CONTROL *the_chain);


/* 
 *  _Chain_Is_null_node
 *
 *  This function returns TRUE if the_node is NULL and FALSE otherwise.
 */
BOOL _Chain_Is_null_node(CHAIN_NODE *the_node);


/* 
 *  Chain_Initialize
 *
 *  This routine initializes the_chain structure to manage the
 *  contiguous array of number_nodes nodes which starts at
 *  starting_address.  Each node is of node_size bytes.
 *
 *  Chain_Control					*the_chain,		 * IN  * 
 *  void							 *starting_address,	 * IN  * 
 *  rtems_unsigned32				  number_nodes,		 * IN  * 
 *  rtems_unsigned32				  node_size			 * IN  * 
 */

#define Chain_Initialize( the_chain, starting_address, \
						  number_nodes, node_size ) \
	   _Chain_Initialize( the_chain, starting_address, \
						  number_nodes, node_size ) \


/* 
 *  Chain_Initialize_empty
 *
 *  This routine initializes the specified chain to contain zero nodes.
 *
 *  Chain_Control					*the_chain			 * IN  * 
 */

#define Chain_Initialize_empty( the_chain ) \
	   _Chain_Initialize_empty( the_chain )
 

/*
 *  Chain_Are_nodes_equal
 *
 *  This function returns TRUE if LEFT and RIGHT are equal,
 *  and FALSE otherwise.
 *
 *  Chain_Node					   *left,			 * IN  * 
 *  Chain_Node					   *right			 * IN  * 
 */
 
#define Chain_Are_nodes_equal( left, right ) \
	   _Chain_Are_nodes_equal( left, right )


/* 
 *  Chain_Extract_unprotected
 *
 *  This routine extracts the_node from the chain on which it resides.
 *  It does NOT disable interrupts to insure the atomicity of the
 *  extract operation.
 *
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Extract_unprotected( the_node ) \
	   _Chain_Extract_unprotected( the_node )


/* 
 *  Chain_Extract
 *
 *  This routine extracts the_node from the chain on which it resides.
 *  It disables interrupts to insure the atomicity of the
 *  extract operation.
 *
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Extract( the_node ) \
	   _Chain_Extract( the_node )


/* 
 *  Chain_Get_unprotected
 *
 *  This function removes the first node from the_chain and returns
 *  a pointer to that node.  If the_chain is empty, then NULL is returned.
 *  It does NOT disable interrupts to insure the atomicity of the
 *  get operation.
 *
 *  Chain_Control					*the_chain			 * IN  * 
 */

#define Chain_Get_unprotected( the_chain ) \
	   _Chain_Get_unprotected( the_chain )


/* 
 *  Chain_Get
 *
 *  This function removes the first node from the_chain and returns
 *  a pointer to that node.  If the_chain is empty, then NULL is returned.
 *  It disables interrupts to insure the atomicity of the
 *  get operation.
 *
 *  Chain_Control					*the_chain			 * IN  * 
 */

#define Chain_Get( the_chain ) \
	   _Chain_Get( the_chain )


/* 
 *  Chain_Get_first_unprotected
 *
 *  This function removes the first node from the_chain and returns
 *  a pointer to that node.  It does NOT disable interrupts to insure
 *  the atomicity of the get operation.
 *
 *  Chain_Control					*the_chain			 * IN  * 
 */

#define Chain_Get_first_unprotected( the_chain ) \
	   _Chain_Get_first_unprotected( the_chain )


/* 
 *  Chain_Insert_unprotected
 *
 *  This routine inserts the_node on a chain immediately following
 *  after_node.  It does NOT disable interrupts to insure the atomicity
 *  of the extract operation.
 *
 *  Chain_Node					   *after_node,		 * IN  * 
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Insert_unprotected( after_node, the_node ) \
	   _Chain_Insert_unprotected( after_node, the_node )


/* 
 *  Chain_Insert
 *
 *  This routine inserts the_node on a chain immediately following
 *  after_node.  It disables interrupts to insure the atomicity
 *  of the extract operation.
 *
 *  Chain_Node					   *after_node,		 * IN  * 
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Insert( after_node, the_node ) \
	   _Chain_Insert( after_node, the_node )


/* 
 *  Chain_Append_unprotected
 *
 *  This routine appends the_node onto the end of the_chain.
 *  It does NOT disable interrupts to insure the atomicity of the
 *  append operation.
 *
 *  Chain_Control					*the_chain,		 * IN  * 
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Append_unprotected( the_chain, the_node ) \
	   _Chain_Append_unprotected( the_chain, the_node )


/* 
 *  Chain_Append
 *
 *  This routine appends the_node onto the end of the_chain.
 *  It disables interrupts to insure the atomicity of the
 *  append operation.
 *
 *  Chain_Control					*the_chain,		 * IN  * 
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Append( the_chain, the_node ) \
	   _Chain_Append( the_chain, the_node )


/* 
 *  Chain_Prepend_unprotected
 *
 *  This routine prepends the_node onto the front of the_chain.
 *  It does NOT disable interrupts to insure the atomicity of the
 *  prepend operation.
 *
 *  Chain_Control					*the_chain,		 * IN  * 
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Prepend_unprotected( the_chain, the_node ) \
	   _Chain_Prepend_unprotected( the_chain, the_node )


/* 
 *  Chain_Prepend
 *
 *  This routine prepends the_node onto the front of the_chain.
 *  It disables interrupts to insure the atomicity of the
 *  prepend operation.
 *
 *  Chain_Control					*the_chain,		 * IN  * 
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Prepend( the_chain, the_node ) \
	   _Chain_Prepend( the_chain, the_node )


/* 
 *  Chain_Head
 *
 *  This function returns a pointer to the first node on the chain.
 *
 *  Chain_Control					*the_chain			 * IN  * 
 */

#define Chain_Head( the_chain ) \
	   _Chain_Head( the_chain )


/* 
 *  Chain_Tail
 *
 *  This function returns a pointer to the last node on the chain.
 *
 *  Chain_Control					*the_chain			 * IN  * 
 */

#define Chain_Tail( the_chain ) \
	   _Chain_Tail( the_chain )


/* 
 *  Chain_Is_head
 *
 *  This function returns TRUE if the_node is the head of the_chain and
 *  FALSE otherwise.
 *
 *  Chain_Control					*the_chain,		 * IN  * 
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Is_head( the_chain, the_node ) \
	   _Chain_Is_head( the_chain, the_node )


/* 
 *  Chain_Is_tail
 *
 *  This function returns TRUE if the_node is the tail of the_chain and
 *  FALSE otherwise.
 *
 *  Chain_Control					*the_chain,		 * IN  * 
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Is_tail( the_chain, the_node ) \
	   _Chain_Is_tail( the_chain, the_node )


/* 
 *  Chain_Is_first
 *
 *  This function returns TRUE if the_node is the first node on a chain and
 *  FALSE otherwise.
 *
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Is_first( the_node ) \
	   _Chain_Is_first( the_node )


/* 
 *  Chain_Is_last
 *
 *  This function returns TRUE if the_node is the last node on a chain and
 *  FALSE otherwise.
 *
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Is_last( the_node ) \
	   _Chain_Is_last( the_node )


/* 
 *  Chain_Is_empty
 *
 *  This function returns TRUE if there are no nodes on the_chain and
 *  FALSE otherwise.
 *
 *  Chain_Control					*the_chain			 * IN  * 
 */

#define Chain_Is_empty( the_chain ) \
	   _Chain_Is_empty( the_chain )


/* 
 *  Chain_Has_only_one_node
 *
 *  This function returns TRUE if there is only one node on the_chain and
 *  FALSE otherwise.
 *
 *  Chain_Control					*the_chain			 * IN  * 
 */

#define Chain_Has_only_one_node( the_chain ) \
	   _Chain_Has_only_one_node( the_chain )


/* 
 *  Chain_Is_null
 *
 *  This function returns TRUE if the_chain is NULL and FALSE otherwise.
 *
 *  Chain_Control					*the_chain			 * IN  * 
 */

#define Chain_Is_null( the_chain ) \
	   _Chain_Is_null( the_chain )


/* 
 *  Chain_Is_null_node
 *
 *  This function returns TRUE if the_node is NULL and FALSE otherwise.
 *
 *  Chain_Node					   *the_node			 * IN  * 
 */

#define Chain_Is_null_node( the_node ) \
	   _Chain_Is_null_node( the_node )

#endif
/* end of include file */
