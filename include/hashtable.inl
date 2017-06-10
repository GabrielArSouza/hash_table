template< typename KeyType, typename DataType >
bool HashTbl::insert
( const KeyType & k_ , const DataType & d_ )
{
	//<! calcula endereço
	auto end = k_%count();

	//<!tenta inserir
	if ( m_data_table[end].empty() )
	{	
		m_data_table[end].push_front( d_ );
		return true;
	}
	else
	{
		auto i = m_data_table[end].begin();
		auto l = m_data_table[end].end();

		for ( /*empty*/; i != j; ++i )
		{
			if ( *i == d_ )
			{
				*i = d_;
				return false;
			}
		}

		m_data_table[end].push_front( d_ );
	}
	return false;
}

template< typename KeyType, typename DataType >
bool HashTbk::remove
( const KeyType & k_ )
{
	//<! calcula endereço
	auto end = k_%count();

	if ( m_data_table[end].empty() )
		return false;
	else 
	{
		m_data_table[end].clear();
	}
}

template< typename KeyType, typename DataType >
bool HashTbl::retrieve
( const KeyType & k_ , DataType & d_ ) const
{
	//<! calcula endereço
	auto end = k_%count();

	if ( m_data_table[end].empty() )
		return false;

	return true;
}

template< typename KeyType, typename DataType >
void HashTbl::clear ( void )
{
	for ( auto i(0); i < m_size; ++i)
			m_data_table[i].clear();
}

template< typename KeyType, typename DataType >
bool HashTbl::empty ( void ) const
{
	for ( auto i(0); i < m_size; ++i )
		if ( !m_data_table[i].empty() )
			return false;

	return true;
}

template< typename KeyType, typename DataType >
unsigned long int HashTbl::count
( void ) const
{
	return m_count;
}

template< typename KeyType, typename DataType >
void Hash::print () const
{
	std::cout << "\n TABLE \n [ ";
	for ( auto i(0); i < m_size; ++i )
	{
		if ( !m_data_table[i].empty() )
		{
			std::cout << "| ";
			auto i = m_data_table[i].begin();
			while ( i != m_data_table[i].end() )
			{
				std::cout << *i << " ";
				++i;
			}
			std::cout << "| ";
		}else { std::cout << "| 0 |"; }
	}
}


