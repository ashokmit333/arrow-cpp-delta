import my_module
import pandas as pd
import pyarrow as pa
from deltalake import write_deltalake

# Get the list of SignalLogging objects from the C++ function
signals = my_module.get_signal_loggings()

signals_data = [{
    "aliasKey": signal.aliasKey,
    "channelDevice": signal.channelDevice,
    "channelGroupId": signal.channelGroupId,
    "channelGroupIdx": signal.channelGroupIdx
} for signal in signals]




# Convert the list of dictionaries into a pandas DataFrame
df = pd.DataFrame(signals_data)

# Convert the pandas DataFrame into an Arrow Table
table = pa.Table.from_pandas(df)

write_deltalake(
    "abc",
    table,
    mode="overwrite",
    engine="rust",)
