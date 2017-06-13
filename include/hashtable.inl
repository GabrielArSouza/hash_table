/**
 * @file hashtable.inl
 * @author Gabriel Araújo de Souza
 * @date 13 Jun 2017
 * @brief Arquivo contendo a implementação da classe HashTbl
 */

bool is_prime ( int p )
{
	if ( p == 0 ) return false;
	if ( p == 1 ) return true;
	auto r = std::sqrt(p);

	for ( auto i(2); i <= r; i++)
	{
		if ( p%i == 0 ) return false;
	}
	return true;
}

int next_prime ( int p )
{
	if ( !is_prime(p) )
	{
		auto aux = ++p;
		while ( !is_prime(aux) ) aux++;
		return aux;
	}
	return p;
}

//<! Insere um novo dado na tabela
template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::insert
( const KeyType & k_ , const DataType & d_ )
{
	if( m_count/m_size >= 1 ) rehash();

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
		m_count++;
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
		m_count++;
	}
	return false;
}

//<! Remove um dado da tabela
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
				m_count--;
				return true;
			}
		}
	}
	return false;
}

//<! Recupera um dado da tabela por meio de uma chave
template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve
( const KeyType & k_ , DataType & d_ ) const
{
	KeyHash hashFunc;  //<! instancia função de dispersão 1
	KeyEqual equalFunc; //<! instancia função de comparação
	                        
	//<! calcula endereço
	auto end( hashFunc(k_) % m_size );

	if ( m_data_table[end].empty() )
		return false;
	else 
	{
		auto i = m_data_table[end].begin();
		auto l = m_data_table[end].end();

		for ( /*empty*/; i != l; ++i )
		{
			if ( equalFunc( (*i).m_key, k_ ) )
			{
				d_ = (*i).m_data;
				return true;
			}
		}
	}
	return false;
}

//<! Remove todos os dados da tabela
template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::clear ( void )
{
	for ( auto i(0u); i < m_size; ++i)
			m_data_table[i].clear();
	m_count = 0;
}

//<! Verifica se a tabela está vazia
template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::empty ( void ) const
{
	for ( auto i(0u); i < m_size; ++i )
		if ( !m_data_table[i].empty() )
			return false;

	return true;
}

//<! Retorna a quantidade de elementos presentes na tabela
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

//<! imprime a tabela na saída padrão
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

//<! retorna a quantidade de posições da tabela
template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
unsigned int
HashTbl<KeyType, DataType, KeyHash, KeyEqual>::capacity() const
{
	return m_size;
}

//<! Dobra o tamanho da tabela
template< typename KeyType,
		  typename DataType,
		  typename KeyHash,
		  typename KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::rehash ()
{
	int aux = m_size*2;
	auto new_size = next_prime(aux);
	KeyHash hashFunc;  //<! instancia função de dispersão 1
	
	auto temp = new std::forward_list<Entry>[ new_size ];

	for ( auto i(0u); i < m_size; ++i)
	{
		if ( !m_data_table[i].empty() )
		{
			auto f = m_data_table[i].begin();
			auto l = m_data_table[i].end();
			while ( f != l )
			{
				//<! calcula novo endereço
				auto end = hashFunc((*f).m_key) % new_size;
				//<! insere o elemento na nova lista
				Entry new_entry ((*f).m_key, (*f).m_data );
				temp[end].push_front( new_entry );
				++f;
			}
		}
	} 

	//<! desaloca memória
	delete [] m_data_table;

	//<! aponta para a nova tabela
	m_data_table = temp;
	m_size = new_size;	

}

