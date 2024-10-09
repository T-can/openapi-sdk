package com.longport.trade;

import java.math.BigDecimal;

import com.longport.Market;

public class StockPosition {
    private String symbol;
    private String symbolName;
    private BigDecimal quantity;
    private BigDecimal availableQuantity;
    private String currency;
    private BigDecimal costPrice;
    private Market market;
    private BigDecimal initQuantity;

    public String getSymbol() {
        return symbol;
    }

    public String getSymbolName() {
        return symbolName;
    }

    public BigDecimal getQuantity() {
        return quantity;
    }

    public BigDecimal getAvailableQuantity() {
        return availableQuantity;
    }

    public String getCurrency() {
        return currency;
    }

    public BigDecimal getCostPrice() {
        return costPrice;
    }

    public Market getMarket() {
        return market;
    }

    public BigDecimal getInitQuantity() {
        return initQuantity;
    }

    @Override
    public String toString() {
        return "StockPosition [symbol=" + symbol + ", symbolName=" + symbolName + ", quantity=" + quantity
                + ", availableQuantity=" + availableQuantity + ", currency=" + currency + ", costPrice=" + costPrice
                + ", market=" + market + ", initQuantity=" + initQuantity + "]";
    }
}
