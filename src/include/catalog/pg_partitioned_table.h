/*-------------------------------------------------------------------------
 *
 * pg_partitioned_table.h
 *	  definition of the system "partitioned table" relation
 *	  along with the relation's initial contents.
 *
 *
 * Portions Copyright (c) 1996-2016, PostgreSQL Global Development Group
 *
 * $PostgreSQL: pgsql/src/include/catalog/pg_partitioned_table.h $
 *
 * NOTES
 *	  the genbki.sh script reads this file and generates .bki
 *	  information from the DATA() statements.
 *
 *-------------------------------------------------------------------------
 */
#ifndef PG_PARTITIONED_TABLE_H
#define PG_PARTITIONED_TABLE_H

#include "catalog/genbki.h"

/* ----------------
 *		pg_partitioned_table definition.  cpp turns this into
 *		typedef struct FormData_pg_partitioned_table
 * ----------------
 */
#define PartitionedRelationId 3350

CATALOG(pg_partitioned_table,3350) BKI_WITHOUT_OIDS
{
	Oid				partrelid;		/* partitioned table oid */
	char			partstrat;		/* partitioning strategy */
	int16			partnatts;		/* number of partition key columns */

	/*
	 * variable-length fields start here, but we allow direct access to
	 * partattrs via the C struct.  That's because the first variable-length
	 * field of a heap tuple can be reliably accessed using its C struct
	 * offset, as previous fields are all non-nullable fixed-length fields.
	 */
	int2vector		partattrs;		/* each member of the array is the
									 * attribute number of a partition key
									 * column, or 0 if the column is actually
									 * an expression */

#ifdef CATALOG_VARLEN
	oidvector		partclass;		/* operator class to compare keys */
	oidvector		partcollation;	/* user-specified collation for keys */
	pg_node_tree	partexprs;		/* list of expressions in the partitioning
									 * key; one item for each zero entry in
									 * partattrs[] */
#endif
} FormData_pg_partitioned_table;

/* ----------------
 *      Form_pg_partitioned_table corresponds to a pointer to a tuple with
 *      the format of pg_partitioned_table relation.
 * ----------------
 */
typedef FormData_pg_partitioned_table *Form_pg_partitioned_table;

/* ----------------
 *      compiler constants for pg_partitioned_table
 * ----------------
 */
#define Natts_pg_partitioned_table				7
#define Anum_pg_partitioned_table_partrelid		1
#define Anum_pg_partitioned_table_partstrat		2
#define Anum_pg_partitioned_table_partnatts		3
#define Anum_pg_partitioned_table_partattrs		4
#define Anum_pg_partitioned_table_partclass		5
#define Anum_pg_partitioned_table_partcollation	6
#define Anum_pg_partitioned_table_partexprs		7

#endif   /* PG_PARTITIONED_TABLE_H */
