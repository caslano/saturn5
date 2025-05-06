from base import CustomShock, RegulatoryShock, ParallelShock
from utils import plot_shock, export_shock_to_csv

maturities = [0.5, 1, 2, 5, 10, 30]

# CustomShock example
custom = CustomShock([(1, 0.01), (5, 0.02), (10, 0.03)])
plot_shock(custom, maturities, "Custom Shock")
export_shock_to_csv(custom, maturities, "custom_shock.csv")

# RegulatoryShock example
reg = RegulatoryShock("steepener")
plot_shock(reg, maturities, "Regulatory Steepener")
export_shock_to_csv(reg, maturities, "reg_shock.csv")

# ParallelShock example
par = ParallelShock(0.015)
plot_shock(par, maturities, "Parallel Shock")
export_shock_to_csv(par, maturities, "parallel_shock.csv")
