#ifndef _HASH_H_
#define _HASH_H

#include <forward_list>
#include <memory>

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

template< typename KeyType, typename DataType >
class HashTbl {

	public:

	using Entry = HashEntry < KeyType , DataType >; //!< Alias
	HashTbl ( int tbl_size_ = DEFAULT_SIZE )
		: m_size( tbl_size_ )
		, m_count( 0 )
	{/*empty*/}

	virtual ~ HashTbl () 
	{
		clear();
		delete m_data_table;
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