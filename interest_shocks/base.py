from abc import ABC, abstractmethod
from typing import List, Tuple
import numpy as np
from scipy.interpolate import interp1d

class InterestRateShock(ABC):
    @abstractmethod
    def get_shock(self, maturity: float) -> float:
        pass

    def get_shocks(self, maturities: List[float]) -> List[float]:
        return [self.get_shock(m) for m in maturities]


class RegulatoryShock(InterestRateShock):
    def __init__(self, scenario: str):
        self.scenarios = {
            'parallel_up': lambda m: 0.025,
            'parallel_down': lambda m: -0.025,
            'steepener': lambda m: 0.005 * m,
            'flattener': lambda m: -0.005 * m,
        }
        if scenario not in self.scenarios:
            raise ValueError(f"Unknown regulatory scenario: {scenario}")
        self.scenario = scenario

    def get_shock(self, maturity: float) -> float:
        return self.scenarios[self.scenario](maturity)


class CustomShock(InterestRateShock):
    def __init__(self, points: List[Tuple[float, float]]):
        self.points = sorted(points)
        maturities, values = zip(*self.points)
        self.interp = interp1d(maturities, values, kind='linear', fill_value='extrapolate')

    def get_shock(self, maturity: float) -> float:
        return float(self.interp(maturity))


class ParallelShock(InterestRateShock):
    def __init__(self, shock_value: float):
        self.shock_value = shock_value

    def get_shock(self, maturity: float) -> float:
        return self.shock_value
