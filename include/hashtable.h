#ifndef _HASH_H_
#define _HASH_H

#include <forward_list>
#include <memory>
#include <functional>
#include <iomanip>

template <class KeyType, class DataType>
class HashEntry {
	
	public:

	HashEntry( KeyType k_ , DataType d_ ) 
		: m_key( k_ )
		, m_data ( d_ )
	{ /* Empty */ };
	
	KeyType m_key ;   //!< Stores the key for an entry .
	DataType m_data ; //!< Stores the data for an entry .

};

template< typename KeyType,
		  typename DataType,
		  typename KeyHash = std::hash < KeyType >,
		  typename KeyEqual = std::equal_to < KeyType > >
class HashTbl {

	using Entry = HashEntry < KeyType , DataType >; //!< Alias
	public:

	HashTbl ( int tbl_size_ = DEFAULT_SIZE )
		: m_size( tbl_size_ )
		, m_count( 0 )
		, m_data_table( new std::forward_list< Entry >[tbl_size_] )
	{/*empty*/}

	virtual ~ HashTbl () 
	{
		clear();
		m_data_table.get_deleter();
	}

	bool insert ( const KeyType & k_ , const DataType & d_ );

	bool remove ( const KeyType & k_ );

	bool retrieve ( const KeyType & k_ , DataType & d_ ) const;

	void clear ( void );

	bool empty ( void ) const;

	unsigned long int count ( void ) const;

	void print () const ;

	private:

	void rehash (); //!< Change Hash table size if load factor λ > 1.0
	unsigned int m_size ; //!< Hash table size .
	unsigned int m_count ; //!< Number of elements currently stored in the table .
	                    
	//! < The table : array of pointers to collision list .
	//std::forward_list <Entry> *m_data_table ;
	std::unique_ptr< std::forward_list< Entry >[] > m_data_table;
	//! Hash table’s default size : 11 table entries .
	static const short DEFAULT_SIZE = 11;
};

#include "hashtable.inl"

#endif