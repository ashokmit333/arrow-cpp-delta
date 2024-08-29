import pyarrow as pa
import pandas as pd
pa.get_include()
import pyarrow.parquet as pq
import pyarrow.fs as fs
from deltalake import write_deltalake


def processtable(table):
    print(table)
    write_deltalake(
    "abc",
    table,
    mode="overwrite",
    engine="rust",)
    return "Success"

    # df = table.to_pandas()
    # print(df)
    # local_fs = fs.LocalFileSystem()
    # parquet_file_path = 'abc.parquet'
    # with pq.ParquetWriter(parquet_file_path, table.schema,filesystem=local_fs) as writer:
    # # Write the Arrow Table to the Parquet file
    #     writer.write_table(table)