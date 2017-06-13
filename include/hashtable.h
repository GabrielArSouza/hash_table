/**
 * @file hashtable.h
 * @author Gabriel Araújo de Souza
 * @date 13 Jun 2017
 * @brief Arquivo contendo as definições das classes HashEntry e HashTbl
 */

#ifndef _HASH_H_
#define _HASH_H

#include <forward_list> //<! std::forward_list e seus métodos
#include <memory>		//<! std::unique_ptr, get_deleter() 
#include <functional>	
#include <iomanip>		 
#include <cmath> 		//<! std::sqrt

bool is_prime ( int p );

int next_prime ( int p );

/**
 * @brief      Classe para o tipo de dado armazenado na tabela hash.
 *
 * @tparam     KeyType   Chave do dado, tupla definida no main 
 * @tparam     DataType  Tipo do dado a ser armazenado
 */
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

/**
 * @brief      Classe da tabela hash
 *
 * @tparam     KeyType   Chave do dado, tupla definida no main 
 * @tparam     DataType  Tipo do dado a ser armazenado
 * @tparam     KeyHash   Classe que aplica a função de dispersão
 * @tparam     KeyEqual  Compara se duas KeyType são iguais
 */
template< typename KeyType,
		  typename DataType,
		  typename KeyHash = std::hash < KeyType >,
		  typename KeyEqual = std::equal_to < KeyType > >
class HashTbl {

	using Entry = HashEntry < KeyType , DataType >; //!< Alias
	
	public:

	/**
	 * @brief      Construtor
	 *
	 * @param[in]  tbl_size_  tamanho da tabela
	 */
	HashTbl ( int tbl_size_ = DEFAULT_SIZE )
	{
		tbl_size_ = next_prime( tbl_size_ );

		m_size = tbl_size_; 
		m_count = 0 ;
		m_data_table = new std::forward_list<Entry>[ m_size ];
	}

	/**
	 * @brief      Destroi o objeto.
	 */
	virtual ~ HashTbl () 
	{
		clear();
		delete [] m_data_table;
	}

	/**
	 * @brief      Insere um novo dado na tabela
	 *
	 * @param[in]  k_    Chave do dado a ser inserido
	 * @param[in]  d_    Dado a ser inserido
	 *
	 * @return     true caso consiga inserir em uma posição vazia,
	 *             false se houver colisão ou sobrescrita de dados. 
	 */
	bool insert ( const KeyType & k_ , const DataType & d_ );

	/**
	 * @brief      Remove um dado da tabela
	 *
	 * @param[in]  k_    Chave do dado que deve ser removido
	 *
	 * @return     True caso consiga remover, falso se não
	 */
	bool remove ( const KeyType & k_ );

	/**
	 * @brief      Recupera um dado associado a uma chave
	 *
	 * @param[in]  k_    Chave que representa o dado
	 * @param      d_    variável para guardar o dado encontrado
	 *
	 * @return     True se achar o valor, false caso contrário
	 */
	bool retrieve ( const KeyType & k_ , DataType & d_ ) const;

	/**
	 * @brief      Limpa todos os dados da tabela
	 */
	void clear ( void );

	/**
	 * @brief      Verifica se a tabela está vazia
	 *
	 * @return     True se estiver vazia, false caso contrário
	 */
	bool empty ( void ) const;

	/**
	 * @brief      Pega o número de elementos armazenados na tabela
	 *
	 * @return     { description_of_the_return_value }
	 */
	unsigned long int count ( void ) const;

	/**
	 * @brief      Imprime a tabela na saída padrão
	 */
	void print () const ;

	/**
	 * @brief      Pega a quantidade de posições que a tabela possui
	 *
	 * @return     O m_size da tabela.
	 */
	unsigned int capacity() const;

	private:

	void rehash (); 	   //!< Change Hash table size if load factor λ > 1.0
	unsigned int m_size ;  //!< Hash table size .
	unsigned int m_count ; //!< Number of elements currently stored in the table .
	                    
	//! < The table : array of pointers to collision list .
	std::forward_list < Entry > * m_data_table; 

	//! Hash table’s default size : 11 table entries .
	static const short DEFAULT_SIZE = 11;
};

#include "hashtable.inl"

#endif