<style>
/* NAV BAR */
.masthead {
  background-color: #1b5e20 !important;
}

.masthead a {
  color: white !important;
}
.green-box {
  background-color: #e8f5e9;
  border: 2px solid #1b5e20;
  padding: 15px;
  border-radius: 8px;
  margin: 20px 0;
}
</style>


---
layout: single
---

Welcome! This site will contain the following, an about me, my GIS and Arduino projects, my current academic publications, and an up to date resume. Use the navigation bar at the top of the screen to view everything. 

<h2>Recent Projects</h2>

{% assign all_projects = site.projectsgis | concat: site.projectsarduino | sort: "date" | reverse %}

<ul>
  {% for project in all_projects limit: 5 %}
    <li>
      <a href="{{ project.url }}">{{ project.title }}</a><br>
      <small>{{ project.date | date: "%b %d, %Y" }}</small>
      <p>{{ project.excerpt }}</p>
    </li>
  {% endfor %}
</ul>
