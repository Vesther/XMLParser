# A (very) basic C++ XML Parser
This is my horrible hack of a XML Parser for a very simple subset of XML.

The list of things it doesn't support is very long, including comments, XML declaration and processing instruction tags.

Here are some examples of things it CAN parse correctly:

```xml
<catalog>
    <book id="bk101">
        <author>Gambardella, Matthew</author>
        <title>XML Developer's Guide</title>
        <genre>Computer</genre>
        <price>44.95</price>
        <publish_date>2000-10-01</publish_date>
        <description>An in-depth look at creating applications with XML.</description>
    </book>
    <book id="bk102">
        <author>Ralls, Kim</author>
        <title>Midnight Rain</title>
        <genre>Fantasy</genre>
        <price>5.95</price>
        <publish_date>2000-12-16</publish_date>
        <description>A former architect battles corporate zombies, an evil sorceress, and her own childhood to become queen of the world.</description>
    </book>
</catalog>
```
---
```xml
<settings version="1.0">
    <widget name="Test">
        <common>
            <param tag="fontSize">
                <int>24</int>
            </param>
        </common>
        <param tag="itemWidth">
            <int>720</int>
        </param>
        <param tag="itemHeight">
            <int>480</int>
        </param>
    </widget>
</settings>
```
