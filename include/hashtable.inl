template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::insert
( const KeyType & k_ , const DataType & d_ )
{
	KeyHash hashFunc;  //<! instancia função de dispersão 1
	KeyEqual equalFunc; //<! instancia função de comparação
	
	//<! criar nova entrada
	Entry new_entry ( k_, d_ );

	//<! calcula o endereço
	auto end( hashFunc(k_) % m_size );
	
	//<! tenta inserir
	if ( m_data_table[end].empty() )
	{	
		m_data_table[end].push_front( new_entry );
		return true;
	}
	else
	{
		auto i = m_data_table[end].begin();
		auto l = m_data_table[end].end();

		for ( /*empty*/; i != l; ++i )
		{
			if ( equalFunc( (*i).m_key, new_entry.m_key ) )
			{
				(*i).m_data = d_;
				return false;
			}
		}

		m_data_table[end].push_front( new_entry );
	}
	return false;
}

template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::remove
( const KeyType & k_ )
{
	KeyHash hashFunc;  //<! instancia função de dispersão 1
	KeyEqual equalFunc; //<! instancia função de comparação
	
	//<! calcula endereço
	auto end( hashFunc(k_) % m_size );

	if ( m_data_table[end].empty() )
		return false;
	else 
	{
		auto target = m_data_table[end].before_begin();
		auto it = m_data_table[end].begin();

		for ( /*empty*/; it != m_data_table[end].end(); ++it, ++target)
		{
			if ( equalFunc((*it).m_key, k_ ))
			{
				m_data_table[end].erase_after( target );
				return true;
			}
		}
	}
	return false;
}

template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve
( const KeyType & k_ , DataType & d_ ) const
{
	//<! calcula endereço
	auto end = k_%count();

	if ( m_data_table[end].empty() )
		return false;

	return true;
}

template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::clear ( void )
{
	for ( auto i(0u); i < m_size; ++i)
			m_data_table[i].clear();
}

template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::empty ( void ) const
{
	for ( auto i(0); i < m_size; ++i )
		if ( !m_data_table[i].empty() )
			return false;

	return true;
}

template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
unsigned long int
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::count
( void ) const
{
	return m_count;
}

template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::print () const
{
	/*cabeçalho*/
	
	std::cout << "[ ID, NAME, BANK, BRANCH, ACCOUNT, BALANCE ]\n";
	std::cout << "\n";
	for ( auto i(0u); i < m_size; ++i )
	{
		if ( !(m_data_table[i].empty()) )
		{
			auto j = m_data_table[i].begin();
			while ( j != m_data_table[i].end() )
			{
				auto aux = (*j).m_data;
				std::cout << "[ " << i << ", ";
				std::cout << aux.name << ", ";
				std::cout << aux.bank << ", ";
				std::cout << aux.branch << ", ";
				std::cout << aux.account << ", ";
				std::cout << aux.balance << " ]";
				std::cout << "\n";
				++j;
			}
			
		}
	}
}


