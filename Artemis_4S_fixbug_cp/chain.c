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


#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "chain.h"
#include "includes.h"

/*PAGE
 *
 *  _Chain_Initialize
 *
 *  This kernel routine initializes a doubly linked chain. 
 *
 *  Input parameters:
 *	the_chain		- pointer to chain header
 *	starting_address - starting address of first node
 *	number_nodes	 - number of nodes in chain
 *	node_size		- size of node in bytes
 *
 *  Output parameters:  NONE
 */

VOID _Chain_Initialize ( 
						 CHAIN_CONTROL  *the_chain,
						 VOID		   *starting_address,
						 UINT32		  number_nodes,
						 UINT32		  node_size
						)
{
	UINT32	  count; 
	CHAIN_NODE *current;
	CHAIN_NODE *next;


	count					 = number_nodes;
	current				   = _Chain_Head( the_chain );
	the_chain->permanent_null = NULL;
	next					  = (CHAIN_NODE *)starting_address;

	while ( count-- ) {
		current->next  = next;
		next->previous = current;
		current		= next;
		next		   = (CHAIN_NODE *)_Addresses_Add_offset((VOID *)next, node_size);
	}

	current->next	= _Chain_Tail( the_chain );
	the_chain->last  = current;
}


/*PAGE
 *
 *  Chain_Initialize_empty
 */

VOID _Chain_Initialize_empty (CHAIN_CONTROL *the_chain)
{
	the_chain->first		  = _Chain_Tail( the_chain );
	the_chain->permanent_null = NULL;
	the_chain->last		   = _Chain_Head( the_chain );
}


/*PAGE
 *
 *  _Chain_Get_first_unprotected
 */

CHAIN_NODE *_Chain_Get_first_unprotected (CHAIN_CONTROL *the_chain)
{ 
	CHAIN_NODE  *return_node;
	CHAIN_NODE  *new_first;

	return_node		 = the_chain->first;
	new_first		   = return_node->next;
	the_chain->first	= new_first;
	new_first->previous = _Chain_Head( the_chain );

	return return_node;
}


/*PAGE
 *
 *  _Chain_Get
 *
 *  This kernel routine returns a pointer to a node taken from the
 *  given chain.
 *
 *  Input parameters:
 *	the_chain - pointer to chain header
 * 
 *  Output parameters: 
 *	return_node - pointer to node in chain allocated
 *	CHAIN_END   - if no nodes available
 * 
 *  INTERRUPT LATENCY:
 *	only case
 */

CHAIN_NODE *_Chain_Get (CHAIN_CONTROL *the_chain)
{
	CHAIN_NODE *return_node;

	return_node = NULL;

	CHAIN_ENTER_CRITICAL();

	if ( !_Chain_Is_empty( the_chain ) ) 
		return_node = _Chain_Get_first_unprotected( the_chain );
	  
	CHAIN_EXIT_CRITICAL(); 

	return return_node;
}


/*PAGE
 *
 *  _Chain_Append
 *
 *  This kernel routine puts a node on the end of the specified chain.
 *
 *  Input parameters:
 *	the_chain - pointer to chain header
 *	node	  - address of node to put at rear of chain
 * 
 *  Output parameters:  NONE
 * 
 *  INTERRUPT LATENCY:
 *	only case
 */

VOID _Chain_Append (CHAIN_CONTROL *the_chain, CHAIN_NODE *node)
{
	CHAIN_ENTER_CRITICAL();
	_Chain_Append_unprotected( the_chain, node );
	CHAIN_EXIT_CRITICAL(); 
}


/*PAGE
 *
 *  _Chain_Extract
 *
 *  This kernel routine deletes the given node from a chain.
 *
 *  Input parameters:
 *	node - pointer to node in chain to be deleted
 * 
 *  Output parameters:  NONE
 * 
 *  INTERRUPT LATENCY:
 *	only case
 */

VOID _Chain_Extract (CHAIN_NODE *node)
{ 
	CHAIN_ENTER_CRITICAL();
	_Chain_Extract_unprotected( node );
	CHAIN_EXIT_CRITICAL();
}


/*PAGE
 *
 *  _Chain_Insert
 *
 *  This kernel routine inserts a given node after a specified node
 *  a requested chain.
 *
 *  Input parameters:
 *	after_node - pointer to node in chain to be inserted after
 *	node	   - pointer to node to be inserted
 * 
 *  Output parameters:  NONE
 * 
 *  INTERRUPT LATENCY:
 *	only case
 */

VOID _Chain_Insert (CHAIN_NODE *after_node, CHAIN_NODE *node)
{
	CHAIN_ENTER_CRITICAL();
	_Chain_Insert_unprotected( after_node, node );
	CHAIN_EXIT_CRITICAL(); 
}


/*PAGE
 *
 *  _Chain_Insert_chain 
 *
 *  This routine inserts a chain after the specified node in another
 *  chain. It is assumed that the insert after node is not on the 
 *  second chain. 
 *
 *  Input parameters:
 *	insert_after - insert the chain after this node
 *	to_insert	- the chain to insert
 */ 
 
VOID _Chain_Insert_chain (CHAIN_NODE *insert_after, CHAIN_CONTROL *to_insert)
{
	CHAIN_NODE *first;
	CHAIN_NODE *last;
	CHAIN_NODE *insert_after_next;

	first = to_insert->first;
	last = to_insert->last;

	insert_after_next = insert_after->next;

	insert_after->next = first;
	first->previous	= insert_after;

	insert_after_next->previous = last;
	last->next				  = insert_after_next;

	_Chain_Initialize_empty( to_insert );
}


/*PAGE
 *  BOOL
 *  _Chain_Is_null
 */

BOOL  _Chain_Is_null (CHAIN_CONTROL *the_chain)
{
	return ( the_chain == NULL );
}


/*PAGE
 *
 *  _Chain_Is_null_node
 */

BOOL _Chain_Is_null_node (CHAIN_NODE *the_node)
{
	return ( the_node == NULL );
}


/*PAGE
 *
 *  _Chain_Head
 */

CHAIN_NODE *_Chain_Head (CHAIN_CONTROL *the_chain)
{
	return (CHAIN_NODE *) the_chain;
}


/*PAGE
 *
 *  _Chain_Tail
 *   链表的最后一个单元指向the_chain->permanent_null的地址.显然,它是一个无效的单元.
 *   应用中应该抛弃它.  eric.
 */

CHAIN_NODE *_Chain_Tail (CHAIN_CONTROL *the_chain)
{
	return (CHAIN_NODE *) &the_chain->permanent_null;
}


/*PAGE
 *
 *  _Chain_Is_empty
 */

BOOL _Chain_Is_empty (CHAIN_CONTROL *the_chain)
{
	return ( the_chain->first == _Chain_Tail( the_chain ) );
}


/*PAGE
 *
 *  _Chain_Is_first
 *  它和_Chain_Is_head一样可以达到同样的效果.
 */

BOOL _Chain_Is_first (CHAIN_NODE *the_node)
{
	return ( the_node->previous == NULL );
}


/*PAGE
 *
 *  _Chain_Is_last
 *  它和_Chain_Is_tail一样可以达到同样的效果.
 */

BOOL _Chain_Is_last (CHAIN_NODE *the_node)
{
	return ( the_node->next == NULL );
}


/*PAGE
 *
 *  _Chain_Has_only_one_node
 */

BOOL _Chain_Has_only_one_node (CHAIN_CONTROL *the_chain)
{
	return ( the_chain->first == the_chain->last );
}


/*PAGE
 *
 *  _Chain_Is_head
 */

BOOL _Chain_Is_head (CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node)
{
	return ( the_node == _Chain_Head( the_chain ) );
}


/*PAGE
 *
 *  _Chain_Is_tail
 */

BOOL _Chain_Is_tail (CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node)
{
	return ( the_node == _Chain_Tail( the_chain ) );
}


/*PAGE
 *
 *  _Chain_Extract_unprotected
 */

VOID _Chain_Extract_unprotected (CHAIN_NODE *the_node)
{
	CHAIN_NODE *next;
	CHAIN_NODE *previous;

	next		   = the_node->next;
	previous	   = the_node->previous;
	next->previous = previous;
	previous->next = next;
}


/*PAGE
 *
 *  Chain_Get_unprotected
 */

CHAIN_NODE *_Chain_Get_unprotected (CHAIN_CONTROL *the_chain)
{ 
	if ( !_Chain_Is_empty( the_chain ) ) 
		return _Chain_Get_first_unprotected( the_chain );
	else
		return NULL;
}


/*PAGE
 *
 *  _Chain_Insert_unprotected
 */

VOID _Chain_Insert_unprotected (CHAIN_NODE *after_node,CHAIN_NODE *the_node)
{
	CHAIN_NODE *before_node;

	the_node->previous	= after_node;
	before_node		   = after_node->next;
	after_node->next	  = the_node; 
	the_node->next		= before_node; 
	before_node->previous = the_node; 
}


/*PAGE
 *
 *  _Chain_Append_unprotected
 *  当链表插入第一个单元时, old_last_node 指向the_chain的first的地址;
 *  所以, old_last_node->next = the_node; 改写了the_chain->first;
 *  eric
 */

VOID _Chain_Append_unprotected (CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node)
{
	CHAIN_NODE *old_last_node;

	the_node->next	  = _Chain_Tail( the_chain );
	old_last_node	   = the_chain->last;
	the_chain->last	 = the_node;
	old_last_node->next = the_node;
	the_node->previous  = old_last_node;
}


/*PAGE
 *
 *  _Chain_Prepend_unprotected
 */

VOID _Chain_Prepend_unprotected (CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node)
{
	_Chain_Insert_unprotected(_Chain_Head( the_chain ), the_node);

}


/*PAGE
 *
 *  _Chain_Prepend
 */

VOID _Chain_Prepend (CHAIN_CONTROL *the_chain, CHAIN_NODE *the_node)
{
	_Chain_Insert(_Chain_Head(the_chain), the_node);
}


