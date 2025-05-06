import matplotlib.pyplot as plt
import pandas as pd
from typing import List
from .base import InterestRateShock

def plot_shock(shock: InterestRateShock, maturities: List[float], title: str = "Shock Curve"):
    shocks = shock.get_shocks(maturities)
    plt.figure(figsize=(8, 4))
    plt.plot(maturities, shocks, marker='o')
    plt.title(title)
    plt.xlabel("Maturity (Years)")
    plt.ylabel("Shock Value")
    plt.grid(True)
    plt.tight_layout()
    plt.show()

def export_shock_to_csv(shock: InterestRateShock, maturities: List[float], filename: str = "shock_curve.csv"):
    shocks = shock.get_shocks(maturities)
    df = pd.DataFrame({"Maturity": maturities, "Shock": shocks})
    df.to_csv(filename, index=False)
    print(f"Shock curve exported to '{filename}'")
