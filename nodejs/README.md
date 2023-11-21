# LongPort OpenAPI SDK for Node.js

`longport` provides an easy-to-use interface for invokes [`LongPort OpenAPI`](https://open.longportapp.com/en/).

## Quickstart

_Install LongPort OpenAPI SDK_

```bash
npm install longport
```

_Setting environment variables(MacOS/Linux)_

```bash
export LONGPORT_APP_KEY="App Key get from user center"
export LONGPORT_APP_SECRET="App Secret get from user center"
export LONGPORT_ACCESS_TOKEN="Access Token get from user center"
```

_Setting environment variables(Windows)_

```powershell
setx LONGPORT_APP_KEY "App Key get from user center"
setx LONGPORT_APP_SECRET "App Secret get from user center"
setx LONGPORT_ACCESS_TOKEN "Access Token get from user center"
```

## Quote API _(Get basic information of securities)_

```javascript
const { Config, QuoteContext } = require("longport");

let config = Config.fromEnv();
QuoteContext.new(config)
    .then((ctx) => ctx.quote(["700.HK", "AAPL.US", "TSLA.US", "NFLX.US"]))
    .then((resp) => {
        for (let obj of resp) {
            console.log(obj.toString())
        }
    });
```

## Quote API _(Subscribe quotes)_

```javascript
const { Config, QuoteContext, SubType } = require("longport");

let config = Config.fromEnv();
QuoteContext.new(config).then((ctx) => {
  ctx.setOnQuote((_, event) => console.log(event.toString()));
  ctx.subscribe(
    ["700.HK", "AAPL.US", "TSLA.US", "NFLX.US"],
    [SubType.Quote],
    true
  );
});
```

## Trade API _(Submit order)_

```javascript
const {
  Config,
  TradeContext,
  Decimal,
  OrderSide,
  TimeInForceType,
  OrderType,
} = require("longport");

let config = Config.fromEnv();
TradeContext.new(config)
  .then((ctx) =>
    ctx.submitOrder({
      symbol: "700.HK",
      orderType: OrderType.LO,
      side: OrderSide.Buy,
      timeInForce: TimeInForceType.Day,
      submittedPrice: new Decimal("50"),
      submittedQuantity: 200,
    })
  )
  .then((resp) => console.log(resp.toString()));
```

## License

Licensed under either of

* Apache License, Version 2.0,([LICENSE-APACHE](./LICENSE-APACHE) or http://www.apache.org/licenses/LICENSE-2.0)
* MIT license ([LICENSE-MIT](./LICENSE-MIT) or http://opensource.org/licenses/MIT) at your option.
