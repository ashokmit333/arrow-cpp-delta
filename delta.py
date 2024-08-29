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
