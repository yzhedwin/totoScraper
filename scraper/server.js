const express = require("express");
const axios = require("axios");
const cors = require("cors");
const cheerio = require("cheerio");
const pretty = require("pretty");
const port = 4000;
const app = express(cors);
const url =
  "https://www.singaporepools.com.sg/en/product/sr/Pages/toto_results.aspx";

async function getResult() {
  let res = [];
  try {
    const { data } = await axios.get(url);
    //Get Cheerio object
    const $ = cheerio.load(data);
    //Get win1 - win6, additional
    let count = 1;
    while (count <= 6) {
      const num = parseInt(cheerio.text($(".win" + count)));
      res.push(num);
      count++;
    }
    const num = parseInt(cheerio.text($(".additional")));
    res.push(num);
  } catch (error) {
    console.log(error);
  }
  res.sort((a, b) => a - b);
  return res;
}

app.get("/toto", async (req, res) => {
  try {
    const result = await getResult();
    let parse = "";
    result.forEach(element => {
      parse = parse + element + " ";
    });
    res.send(parse.trimEnd() + "\n");
    console.log("Result Published")
  } catch (error) {
    console.log(error);
  }
});

app.listen(port, () => {
  console.log(`listening on port :${port}`);
});
